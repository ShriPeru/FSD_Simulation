#include <rclcpp/rclcpp.hpp>
#include <nav_msgs/msg/path.hpp>
#include <geometry_msgs/msg/pose_stamped.hpp>

#include <ompl/base/spaces/DubinsStateSpace.h>
#include <ompl/geometric/SimpleSetup.h>
#include <ompl/geometric/planners/rrt/InformedRRTstar.h>

#include <vector>
#include <cmath>
#include <memory>

namespace ob = ompl::base;
namespace og = ompl::geometric;

/**
 * @brief Represents a circular obstacle in the planning space.
 *
 * Obstacles are modeled as simple circles for collision checking, defined
 * by a center point (x, y) and a radius.
 */
struct Obstacle {
    double x;       ///< X coordinate of the obstacle's center.
    double y;       ///< Y coordinate of the obstacle's center.
    double radius;  ///< Radius of the obstacle.
};

/**
 * @brief The obstacle set currently active for validity checking.
 *
 * OMPL's state validity checker is a plain function, not a bound method,
 * so it has no direct access to per-node data. This global holds the
 * active obstacle set so isStateValid() can reference it during planning.
 */
std::vector<Obstacle> currentObstacles;

/**
 * @brief Determines whether a given planning state is free of collisions.
 *
 * Called internally and repeatedly by OMPL during planning. Extracts the
 * (x, y) position from the state and checks it against every obstacle in
 * currentObstacles using circle-distance math.
 *
 * @param state The candidate state to check, cast internally to an
 *              SE2StateSpace state (DubinsStateSpace is built on SE2).
 * @return true if the state does not collide with any obstacle.
 */
bool isStateValid(const ob::State* state) {
    const auto* se2state = state->as<ob::SE2StateSpace::StateType>();
    double x = se2state->getX();
    double y = se2state->getY();

    const double vehicle_safety_radius = 0.224;  // car's half-diagonal, from size 0.2 x 0.1

    for (const auto& obs : currentObstacles) {
        double dx = x - obs.x;
        double dy = y - obs.y;
        double dist = std::sqrt(dx * dx + dy * dy);
        if (dist < obs.radius + vehicle_safety_radius) {
            return false;
        }
    }
    return true;
}

/**
 * @brief ROS2 node that plans a single global path using Dubins-constrained
 *        RRT* (via OMPL) and publishes it as a nav_msgs/msg/Path.
 *
 * Start, goal, and obstacles are currently hardcoded (matching the
 * project's agreed scope for this stage). The node plans once at startup
 * and publishes the resulting path on the "global_path" topic using a
 * transient-local QoS profile, so that nodes subscribing after the path
 * was published still receive it.
 */
class GlobalPlannerNode : public rclcpp::Node {
public:
    GlobalPlannerNode() : Node("global_planner_node") {
        // Transient-local durability "latches" the last published message,
        // so late-joining subscribers (e.g. a local planner started after
        // this node already planned) still receive the path.
        
        this->declare_parameter("turning_radius", 0.8);
        turning_radius_ = this->get_parameter("turning_radius").as_double();

        rclcpp::QoS qos(1);
        qos.transient_local();

        path_publisher_ = this->create_publisher<nav_msgs::msg::Path>("global_path", qos);

        planAndPublish();
    }

private:
    /**
     * @brief Runs the OMPL Dubins/RRT* planner against a hardcoded
     *        start, goal, and obstacle set, then publishes the result.
     *
     * Logs a warning and publishes nothing if no solution is found
     * within the allotted planning time.
     */
    void planAndPublish() {
        const double start_x = 0.0, start_y = 0.0, start_theta = 0.0;
        const double goal_x = 10.0, goal_y = 10.0, goal_theta = 0.0;
       //  double turning_radius_;
        currentObstacles = {
          {5.0, 5.0, 1.5},
          {3.0, 7.0, 1.0},
          {7.0, 3.0, 1.2},
          {8.0, 8.0, 1.0},
          {2.0, 3.0, 0.8}
        };


        auto space = std::make_shared<ob::DubinsStateSpace>(turning_radius_);

        ob::RealVectorBounds bounds(2);
        bounds.setLow(-20);
        bounds.setHigh(20);
        space->setBounds(bounds);

        og::SimpleSetup ss(space);

        ob::ScopedState<> start(space), goal(space);
        start[0] = start_x; start[1] = start_y; start[2] = start_theta;
        goal[0] = goal_x; goal[1] = goal_y; goal[2] = goal_theta;
        ss.setStartAndGoalStates(start, goal);

        ss.setStateValidityChecker(isStateValid);
        ss.setPlanner(std::make_shared<og::InformedRRTstar>(ss.getSpaceInformation()));

        if (!ss.solve(2.0)) {
            RCLCPP_WARN(this->get_logger(), "Global planner failed to find a solution");
            return;
        }

        ss.simplifySolution();
        publishPath(ss);
    }

    /**
     * @brief Converts a solved OMPL path into a nav_msgs/msg/Path and
     *        publishes it, sampling the solution at fixed intervals.
     *
     * @param ss The SimpleSetup instance holding the solved path.
     */
    void publishPath(og::SimpleSetup& ss) {
        auto& solution_path = ss.getSolutionPath();
        solution_path.interpolate();  // fills in intermediate states along each segment

        nav_msgs::msg::Path path_msg;
        path_msg.header.stamp = this->now();
        path_msg.header.frame_id = "map";

        for (std::size_t i = 0; i < solution_path.getStateCount(); ++i) {
            const auto* state = solution_path.getState(i)->as<ob::SE2StateSpace::StateType>();

            geometry_msgs::msg::PoseStamped pose;
            pose.header = path_msg.header;
            pose.pose.position.x = state->getX();
            pose.pose.position.y = state->getY();
            pose.pose.position.z = 0.0;

            // Convert heading (yaw) into a quaternion for pose.orientation
            double yaw = state->getYaw();
            pose.pose.orientation.z = std::sin(yaw / 2.0);
            pose.pose.orientation.w = std::cos(yaw / 2.0);

            path_msg.poses.push_back(pose);
        }

        path_publisher_->publish(path_msg);
        RCLCPP_INFO(this->get_logger(), "Published global path with %zu waypoints",
                    path_msg.poses.size());
    }

    rclcpp::Publisher<nav_msgs::msg::Path>::SharedPtr path_publisher_;
    double turning_radius_;
};

int main(int argc, char** argv) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<GlobalPlannerNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
