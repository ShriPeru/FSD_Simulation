#include <ompl/base/spaces/DubinsStateSpace.h>
#include <ompl/geometric/SimpleSetup.h>
#include <ompl/geometric/planners/rrt/InformedRRTstar.h>
#include <iostream>
#include <vector>
#include <cmath>
#include <string>

namespace ob = ompl::base;
namespace og = ompl::geometric;

/**
 * @brief Represents a circular obstacle in the planning space.
 *
 * Obstacles are modeled as simple circles for collision checking, defined
 * by a center point (x, y) and a radius. This is the simplest possible
 * collision shape and is sufficient for early-stage obstacle avoidance
 * testing before more complex geometry is introduced.
 */
struct Obstacle {
    double x;       ///< X coordinate of the obstacle's center.
    double y;       ///< Y coordinate of the obstacle's center.
    double radius;  ///< Radius of the obstacle, in the same units as the planning space.
};

/**
 * @brief The obstacle set currently active for validity checking.
 *
 * Because OMPL's state validity checker is a plain function (not a bound
 * method with access to per-test data), this global is reassigned before
 * each test scenario runs so that isStateValid() can check candidate
 * states against the correct obstacle set for that scenario.
 */
std::vector<Obstacle> currentObstacles;

/**
 * @brief Determines whether a given planning state is free of collisions.
 *
 * Called internally and repeatedly by OMPL during planning (during sampling,
 * tree extension, and rewiring) to determine whether a candidate state is
 * usable. Extracts the (x, y) position from the state and checks it against
 * every obstacle in currentObstacles using simple circle-distance math.
 *
 * @param state The candidate state to check, provided by OMPL as an
 *              opaque, generic state pointer. Cast internally to an
 *              SE2StateSpace state, since DubinsStateSpace is built on
 *              top of SE2 (2D position + heading).
 * @return true if the state does not collide with any obstacle, false
 *         if it lies inside one or more obstacles.
 */
bool isStateValid(const ob::State* state) {
    const auto* se2state = state->as<ob::SE2StateSpace::StateType>();
    double x = se2state->getX();
    double y = se2state->getY();

    for (const auto& obs : currentObstacles) {
        double dx = x - obs.x;
        double dy = y - obs.y;
        double dist = std::sqrt(dx * dx + dy * dy);
        if (dist < obs.radius) {
            return false;
        }
    }
    return true;
}

/**
 * @brief Configures and runs a single Dubins-constrained RRT* planning scenario.
 *
 * Sets up an OMPL DubinsStateSpace with the given turning radius, assigns
 * the provided obstacle set as the active validity-checking context, runs
 * Informed RRT* for up to 2 seconds, and prints the resulting path (or a
 * failure message if no solution was found within the time budget).
 *
 * This function is the shared planning harness used by every named test
 * case below, so that each test case only needs to describe its scenario
 * (start, goal, obstacles) rather than repeating OMPL setup boilerplate.
 *
 * @param testName       Human-readable label for this scenario, used in
 *                        printed output to identify which test produced
 *                        which result.
 * @param start_x        Start position, X coordinate.
 * @param start_y        Start position, Y coordinate.
 * @param start_theta    Start heading, in radians.
 * @param goal_x         Goal position, X coordinate.
 * @param goal_y         Goal position, Y coordinate.
 * @param goal_theta     Goal heading, in radians.
 * @param obstacles      The set of circular obstacles active for this
 *                        scenario. Pass an empty vector for obstacle-free
 *                        tests.
 * @param turning_radius Minimum turning radius of the modeled vehicle,
 *                        matching the wheelbase/steering-derived radius
 *                        used elsewhere in the project. Defaults to 4.0.
 */
void runPlanningTest(const std::string& testName,
                      double start_x, double start_y, double start_theta,
                      double goal_x, double goal_y, double goal_theta,
                      const std::vector<Obstacle>& obstacles,
                      double turning_radius = 4.0) {
    std::cout << "\n===== " << testName << " =====\n";

    currentObstacles = obstacles;

    auto space = std::make_shared<ob::DubinsStateSpace>(turning_radius);

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

    if (ss.solve(2.0)) {
        ss.simplifySolution();
        double cost = ss.getSolutionPath().length();
        std::cout << testName << ": SOLVED, cost = " << cost << "\n";
        ss.getSolutionPath().print(std::cout);
    } else {
        std::cout << testName << ": FAILED to find a solution\n";
    }
}

// ---------------------------------------------------------------------
// Non-obstacle test cases
// ---------------------------------------------------------------------

/**
 * @brief Baseline case: a diagonal path with no obstacles present.
 *
 * Establishes the expected minimum-cost Dubins path length between a
 * fixed start and goal when nothing obstructs it. Used as a reference
 * point for comparing against obstacle-laden scenarios below.
 */
void testDirectPath() {
    runPlanningTest("Direct path, no obstacles",
                     0, 0, 0,
                     10, 10, 0,
                     {});
}

/**
 * @brief Baseline case: start and goal already share the same heading,
 *        directly ahead of one another with no obstacles present.
 *
 * This is close to the simplest possible Dubins scenario (a mostly
 * straight-line path), useful as a sanity check that the planner
 * doesn't introduce unnecessary curvature when none is needed.
 */
void testAlreadyAligned() {
    runPlanningTest("Straight-ahead alignment, no obstacles",
                     0, 0, 0,
                     10, 0, 0,
                     {});
}

// ---------------------------------------------------------------------
// Simple obstacle test cases
// ---------------------------------------------------------------------

/**
 * @brief A single obstacle placed directly on the straight-line path
 *        between start and goal.
 *
 * Confirms that the planner detects an unavoidable direct collision
 * and produces a longer, deviating path instead.
 */
void testSingleObstacleBlockingPath() {
    std::vector<Obstacle> obstacles = {
        {5.0, 5.0, 1.5}
    };
    runPlanningTest("Single obstacle blocking direct path",
                     0, 0, 0,
                     10, 10, 0,
                     obstacles);
}

/**
 * @brief Two obstacles positioned near the direct path between start
 *        and goal, requiring the planner to route around both.
 */
void testTwoObstacles() {
    std::vector<Obstacle> obstacles = {
        {5.0, 5.0, 1.5},
        {3.0, 7.0, 1.0}
    };
    runPlanningTest("Two obstacles near path",
                     0, 0, 0,
                     10, 10, 0,
                     obstacles);
}

// ---------------------------------------------------------------------
// Complex obstacle test cases
// ---------------------------------------------------------------------

/**
 * @brief Two obstacles positioned above and below a straight-line route,
 *        forming a narrow corridor the vehicle must pass through.
 *
 * A meaningfully harder case than obstacles that are simply "nearby":
 * the planner must find a path that threads between two constraints
 * rather than looping around a single one, which stresses the
 * Dubins/RRT* combination more directly.
 */
void testNarrowCorridor() {
    std::vector<Obstacle> obstacles = {
        {5.0, 3.0, 2.0},
        {5.0, 7.0, 2.0}
    };
    runPlanningTest("Narrow corridor between two obstacles",
                     0, 5, 0,
                     10, 5, 0,
                     obstacles);
}

/**
 * @brief Five obstacles scattered irregularly across the planning space.
 *
 * The most demanding scenario in this test file: no single obvious
 * detour exists, so the planner must reason about multiple candidate
 * routes and select the lowest-cost option that avoids all obstacles.
 */
void testManyScatteredObstacles() {
    std::vector<Obstacle> obstacles = {
        {3.0, 3.0, 1.0},
        {6.0, 2.0, 1.2},
        {4.0, 6.0, 1.0},
        {7.0, 7.0, 1.5},
        {2.0, 8.0, 1.0}
    };
    runPlanningTest("Many scattered obstacles",
                     0, 0, 0,
                     10, 10, 0,
                     obstacles);
}

/**
 * @brief Runs all defined test scenarios in sequence, from simplest to
 *        most complex, printing each scenario's result as it completes.
 */
int main() {
    testDirectPath();
    testAlreadyAligned();
    testSingleObstacleBlockingPath();
    testTwoObstacles();
    testNarrowCorridor();
    testManyScatteredObstacles();

    return 0;
}
