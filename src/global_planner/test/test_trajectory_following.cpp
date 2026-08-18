#include <vector>
#include <cmath>
#include <iostream>
#include <limits>

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
 * Starts from the closest waypoint to the vehicle and walks forward along
 * the path, accumulating distance between consecutive waypoints, until the
 * accumulated distance reaches lookahead_distance. If the path ends before
 * that distance is reached, returns the final waypoint.
 *
 * @param path               The path to search along.
 * @param vehicle_x          Vehicle's current X position.
 * @param vehicle_y          Vehicle's current Y position.
 * @param lookahead_distance Desired distance ahead to look, in the same
 *                            units as the path coordinates.
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

    // Path ended before reaching the lookahead distance - return the last point
    return path.back();
}
/**
 * @brief Computes the steering angle needed to arc toward a lookahead point,
 *        using the pure pursuit control law.
 *
 * Given the vehicle's current pose and a target lookahead point, computes
 * the curvature of the unique circular arc that is tangent to the vehicle's
 * current heading and passes through the lookahead point, then converts
 * that curvature into a steering angle using the vehicle's wheelbase.
 *
 * @param vehicle_x     Vehicle's current X position.
 * @param vehicle_y     Vehicle's current Y position.
 * @param vehicle_theta Vehicle's current heading, in radians.
 * @param lookahead     The target point to steer toward.
 * @param wheelbase     Vehicle's wheelbase, used to convert curvature into
 *                      a steering angle via the bicycle model.
 * @return              Steering angle in radians. Positive is a left turn,
 *                      matching the Dubins/OMPL convention used elsewhere
 *                      in this project.
 */
double computeSteeringAngle(double vehicle_x, double vehicle_y, double vehicle_theta,
                             const Waypoint& lookahead, double wheelbase) {
    double dx = lookahead.x - vehicle_x;
    double dy = lookahead.y - vehicle_y;

    // Angle from the vehicle to the lookahead point, in the world frame
    double angle_to_target = std::atan2(dy, dx);

    // alpha: angle between the vehicle's heading and the direction to the target
    double alpha = angle_to_target - vehicle_theta;

    // L: straight-line distance to the lookahead point
    double L = std::sqrt(dx * dx + dy * dy);

    if (L < 1e-6) {
        return 0.0;  // avoid division by zero if the lookahead point coincides with the vehicle
    }

    double curvature = 2.0 * std::sin(alpha) / L;
    double delta = std::atan(curvature * wheelbase);

    return delta;
}
// --- Test cases ---

void testLookaheadOnStraightPath() {
    std::vector<Waypoint> path = {
        {0, 0, 0}, {1, 0, 0}, {2, 0, 0}, {3, 0, 0}, {4, 0, 0}, {5, 0, 0}
    };

    Waypoint result = findLookaheadPoint(path, 0.0, 0.0, 2.5);
    std::cout << "Straight path test: lookahead point = ("
              << result.x << ", " << result.y << ")\n";
    // Expect approximately (3, 0) - first waypoint at/past 2.5m from origin
}

void testLookaheadFromMidPath() {
    std::vector<Waypoint> path = {
        {0, 0, 0}, {1, 0, 0}, {2, 0, 0}, {3, 0, 0}, {4, 0, 0}, {5, 0, 0}
    };

    // Vehicle currently sitting at (2, 0), partway along the path
    Waypoint result = findLookaheadPoint(path, 2.0, 0.0, 2.0);
    std::cout << "Mid-path test: lookahead point = ("
              << result.x << ", " << result.y << ")\n";
    // Expect approximately (4, 0) - 2m ahead of the vehicle's actual position
}

void testLookaheadNearPathEnd() {
    std::vector<Waypoint> path = {
        {0, 0, 0}, {1, 0, 0}, {2, 0, 0}, {3, 0, 0}
    };

    // Lookahead distance longer than remaining path
    Waypoint result = findLookaheadPoint(path, 2.0, 0.0, 5.0);
    std::cout << "Near-path-end test: lookahead point = ("
              << result.x << ", " << result.y << ")\n";
    // Expect (3, 0) - clamped to the final waypoint
}

void testSteeringStraightAhead() {
    // Lookahead point directly ahead, vehicle already facing that way
    Waypoint lookahead = {5, 0, 0};
    double delta = computeSteeringAngle(0, 0, 0, lookahead, 0.4);
    std::cout << "Straight-ahead steering test: delta = " << delta << " (expect ~0)\n";
}

void testSteeringCurvesLeft() {
    // Lookahead point up and to the left of the vehicle's current heading
    Waypoint lookahead = {3, 3, 0};
    double delta = computeSteeringAngle(0, 0, 0, lookahead, 0.4);
    std::cout << "Curve-left steering test: delta = " << delta << " (expect > 0)\n";
}

void testSteeringCurvesRight() {
    // Lookahead point up and to the right of the vehicle's current heading
    Waypoint lookahead = {3, -3, 0};
    double delta = computeSteeringAngle(0, 0, 0, lookahead, 0.4);
    std::cout << "Curve-right steering test: delta = " << delta << " (expect < 0)\n";
}
int main() {
    testLookaheadOnStraightPath();
    testLookaheadFromMidPath();
    testLookaheadNearPathEnd();
    testSteeringStraightAhead();
    testSteeringCurvesLeft();
    testSteeringCurvesRight();
    return 0;
}
