# generated from rosidl_cmake/cmake/rosidl_cmake_aggregate_target-extras.cmake.in

# Create a convenience aggregate target vehicle_msgs::vehicle_msgs
# that links all generated interface targets, so downstream packages can use
# a single modern CMake target name instead of ${vehicle_msgs_TARGETS}.
if(vehicle_msgs_TARGETS AND NOT TARGET vehicle_msgs::vehicle_msgs)
  add_library(vehicle_msgs::vehicle_msgs INTERFACE IMPORTED)
  set_target_properties(vehicle_msgs::vehicle_msgs PROPERTIES
    INTERFACE_LINK_LIBRARIES "${vehicle_msgs_TARGETS}")
endif()
