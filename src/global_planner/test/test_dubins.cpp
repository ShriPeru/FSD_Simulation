#include <gtest/gtest.h>
#include <cmath>

extern "C" {
#include "dubins.h"
}

TEST(DubinsTest, PathLengthAtLeastStraightLineDistance) {
    double q0[3] = {0, 0, 0};
    double q1[3] = {10, 10, 0};
    double rho = 4.0;

    DubinsPath path;
    int result = dubins_shortest_path(&path, q0, q1, rho);
    ASSERT_EQ(result, EDUBOK);

    double straight_line_dist = std::sqrt(10.0*10.0 + 10.0*10.0);
    double dubins_length = dubins_path_length(&path);

    EXPECT_GE(dubins_length, straight_line_dist);
}

TEST(DubinsTest, SamplingAtZeroReturnsStart) {
    double q0[3] = {2, 3, 0.5};
    double q1[3] = {10, 10, 0};
    double rho = 4.0;

    DubinsPath path;
    dubins_shortest_path(&path, q0, q1, rho);

    double q[3];
    dubins_path_sample(&path, 0.0, q);

    EXPECT_NEAR(q[0], q0[0], 1e-6);
    EXPECT_NEAR(q[1], q0[1], 1e-6);
    EXPECT_NEAR(q[2], q0[2], 1e-6);
}

TEST(DubinsTest, EndpointMatchesGoal) {
    double q0[3] = {0, 0, 0};
    double q1[3] = {10, 10, 0};
    double rho = 4.0;

    DubinsPath path;
    dubins_shortest_path(&path, q0, q1, rho);

    double q[3];
    dubins_path_endpoint(&path, q);

    EXPECT_NEAR(q[0], q1[0], 1e-3);
    EXPECT_NEAR(q[1], q1[1], 1e-3);
}
