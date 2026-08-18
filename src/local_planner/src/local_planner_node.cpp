#include <rclcpp/rclcpp.hpp>
#include <nav_msgs/msg/path.hpp>
#include <geometry_msgs/msg/point.hpp>
#include <vehicle_msgs/msg/steering_command.hpp>

#include <vector>
#include <cmath>
#include <limits>
#include <optional>
#include <memory>

using namespace std::chrono_literals;

/**
 * @brief A single 2D waypoint on a path, with heading.
 */
struct Waypoint {
    double x;
    double y;
    double theta;
};

/**
 * @brief Finds the index of the path waypoint closest to a given position.
 *
 * @param path The sequence of waypoints to search.
 * @param x    Query position, X coordinate.
 * @param y    Query position, Y coordinate.
 * @return     Index into path of the closest waypoint.
 */
std::size_t findClosestWaypointIndex(const std::vector<Waypoint>& path, double x, double y) {
    std::size_t closest_index = 0;
    double closest_dist_sq = std::numeric_limits<double>::max();

    for (std::size_t i = 0; i < path.size(); ++i) {
        double dx = path[i].x - x;
        double dy = path[i].y - y;
        double dist_sq = dx * dx + dy * dy;
        if (dist_sq < closest_dist_sq) {
            closest_dist_sq = dist_sq;
            closest_index = i;
        }
    }
    return closest_index;
}

/**
 * @brief Finds a point on the path approximately lookahead_distance ahead
 *        of the vehicle's current position.
 *
 * @param path               The path to search along.
 * @param vehicle_x          Vehicle's current X position.
 * @param vehicle_y          Vehicle's current Y position.
 * @param lookahead_distance Desired distance ahead to look.
 * @return                   The chosen lookahead waypoint.
 */
Waypoint findLookaheadPoint(const std::vector<Waypoint>& path,
                             double vehicle_x, double vehicle_y,
                             double lookahead_distance) {
    std::size_t start_index = findClosestWaypointIndex(path, vehicle_x, vehicle_y);

    double accumulated_dist = 0.0;
    for (std::size_t i = start_index; i + 1 < path.size(); ++i) {
        double dx = path[i + 1].x - path[i].x;
        double dy = path[i + 1].y - path[i].y;
        double segment_dist = std::sqrt(dx * dx + dy * dy);

        accumulated_dist += segment_dist;
        if (accumulated_dist >= lookahead_distance) {
            return path[i + 1];
        }
    }

    return path.back();
}

/**
 * @brief Computes the steering angle needed to arc toward a lookahead point,
 *        using the pure pursuit control law.
 *
 * @param vehicle_x     Vehicle's current X position.
 * @param vehicle_y     Vehicle's current Y position.
 * @param vehicle_theta Vehicle's current heading, in radians.
 * @param lookahead     The target point to steer toward.
 * @param wheelbase     Vehicle's wheelbase.
 * @return              Steering angle in radians. Positive is a left turn.
 */
double computeSteeringAngle(double vehicle_x, double vehicle_y, double vehicle_theta,
                             const Waypoint& lookahead, double wheelbase) {
    double dx = lookahead.x - vehicle_x;
    double dy = lookahead.y - vehicle_y;

    double angle_to_target = std::atan2(dy, dx);
    double alpha = angle_to_target - vehicle_theta;
    double L = std::sqrt(dx * dx + dy * dy);

    if (L < 1e-6) {
        return 0.0;
    }

    double curvature = 2.0 * std::sin(alpha) / L;
    return std::atan(curvature * wheelbase);
}

/**
 * @brief ROS2 node implementing pure pursuit path tracking.
 *
 * Subscribes to a global path and the vehicle's current position, and on a
 * fixed timer, computes a steering angle and speed command to track the
 * path, publishing the result as a vehicle_msgs/msg/SteeringCommand.
 *
 * The lookahead distance, wheelbase, and constant speed are fixed
 * parameters for now; only steering is actively computed each cycle.
 */
class LocalPlannerNode : public rclcpp::Node {
public:
    LocalPlannerNode() : Node("local_planner_node") {

        this->declare_parameter("wheelbase", 0.15);
        this->declare_parameter("lookahead_distance", 1.0);
        wheelbase_ = this->get_parameter("wheelbase").as_double();
        lookahead_distance_ = this->get_parameter("lookahead_distance").as_double();

        rclcpp::QoS path_qos(1);
        path_qos.transient_local();

        path_sub_ = this->create_subscription<nav_msgs::msg::Path>(
            "global_path", path_qos,
            std::bind(&LocalPlannerNode::pathCallback, this, std::placeholders::_1));

        position_sub_ = this->create_subscription<geometry_msgs::msg::Point>(
            "ball_position", 10,
            std::bind(&LocalPlannerNode::positionCallback, this, std::placeholders::_1));

        command_pub_ = this->create_publisher<vehicle_msgs::msg::SteeringCommand>(
            "steering_command", 10);

        control_timer_ = this->create_wall_timer(
            50ms, std::bind(&LocalPlannerNode::controlLoop, this));
    }

private:
    /**
     * @brief Stores the latest received global path, converting it from
     *        nav_msgs/msg/Path into the internal Waypoint representation.
     *
     * @param msg The received path message.
     */
    void pathCallback(const nav_msgs::msg::Path::SharedPtr msg) {
        std::vector<Waypoint> new_path;
        new_path.reserve(msg->poses.size());

        for (const auto& pose_stamped : msg->poses) {
            double qz = pose_stamped.pose.orientation.z;
            double qw = pose_stamped.pose.orientation.w;
            double theta = 2.0 * std::atan2(qz, qw);  // inverse of the sin/cos(yaw/2) encoding used by the publisher

            new_path.push_back({
                pose_stamped.pose.position.x,
                pose_stamped.pose.position.y,
                theta
            });
        }

        path_ = new_path;
        RCLCPP_INFO(this->get_logger(), "Received global path with %zu waypoints", path_.size());
    }

    /**
     * @brief Stores the latest received vehicle position.
     *
     * @param msg The received position message (x, y, yaw packed into a Point).
     */
    void positionCallback(const geometry_msgs::msg::Point::SharedPtr msg) {
        vehicle_x_ = msg->x;
        vehicle_y_ = msg->y;
        vehicle_theta_ = msg->z;
        has_position_ = true;
    }

    /**
     * @brief Fixed-rate control loop: computes and publishes a steering
     *        command if both a path and a current position are available.
     *
     * Runs on a 50ms timer (20Hz), a typical rate for a real-time local
     * planning/control loop.
     */


    void controlLoop() {
        if (path_.empty() || !has_position_) {
            return;
        }

        // Check whether the vehicle has effectively reached the goal
        const Waypoint& goal = path_.back();
        double dx_goal = goal.x - vehicle_x_;
        double dy_goal = goal.y - vehicle_y_;
        double dist_to_goal = std::sqrt(dx_goal * dx_goal + dy_goal * dy_goal);
    
        vehicle_msgs::msg::SteeringCommand cmd;

        if (dist_to_goal < goal_tolerance_) {
            cmd.steering_angle = 0.0;
            cmd.speed = 0.0;
            command_pub_->publish(cmd);
            return;
        }

        Waypoint lookahead = findLookaheadPoint(path_, vehicle_x_, vehicle_y_, lookahead_distance_);
        double delta = computeSteeringAngle(vehicle_x_, vehicle_y_, vehicle_theta_, lookahead, wheelbase_);

        cmd.steering_angle = delta;
        cmd.speed = constant_speed_;
        command_pub_->publish(cmd);
    }

    rclcpp::Subscription<nav_msgs::msg::Path>::SharedPtr path_sub_;
    rclcpp::Subscription<geometry_msgs::msg::Point>::SharedPtr position_sub_;
    rclcpp::Publisher<vehicle_msgs::msg::SteeringCommand>::SharedPtr command_pub_;
    rclcpp::TimerBase::SharedPtr control_timer_;

    std::vector<Waypoint> path_;
    double vehicle_x_ = 0.0;
    double vehicle_y_ = 0.0;
    double vehicle_theta_ = 0.0;
    bool has_position_ = false;

    double lookahead_distance_;
    double wheelbase_;
    const double constant_speed_ = 0.5;
    const double goal_tolerance_ = 0.5;  // meters - how close counts as "arrived"
};

int main(int argc, char** argv) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<LocalPlannerNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
