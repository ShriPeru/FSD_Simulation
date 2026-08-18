#include <rclcpp/rclcpp.hpp>
#include <nav_msgs/msg/path.hpp>
#include <cstdio>

extern "C" {
#include "dubins.h"
}

int main() {
    double q0[3] = {0, 0, 0};
    double q1[3] = {10, 10, 0};
    double turning_radius = 4.0;

    DubinsPath path;
    int result = dubins_shortest_path(&path, q0, q1, turning_radius);
    if (result != EDUBOK) {
        printf("No valid Dubins path found, error code: %d\n", result);
        return 1;
    }

    double length = dubins_path_length(&path);
    printf("Path length: %.2f\n", length);

    for (double t = 0; t < length; t += 1.0) {
        double q[3];
        dubins_path_sample(&path, t, q);
        printf("t=%.1f  x=%.2f  y=%.2f  theta=%.2f\n", t, q[0], q[1], q[2]);
    }

    return 0;
}
