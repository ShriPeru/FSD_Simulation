cmake_minimum_required(VERSION 3.8)
project(mujoco_sim_node)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(ament_index_cpp REQUIRED)
set(MUJOCO_DIR "$ENV{HOME}/mujoco")
find_package(glfw3 REQUIRED)
find_package(vehicle_msgs REQUIRED)
if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()
add_executable(mujoco_sim_node src/mujoco_sim_node.cpp)

target_include_directories(mujoco_sim_node PRIVATE ${MUJOCO_DIR}/include)
target_link_directories(mujoco_sim_node PRIVATE ${MUJOCO_DIR}/lib)
target_link_libraries(mujoco_sim_node mujoco glfw)


ament_target_dependencies(mujoco_sim_node rclcpp geometry_msgs ament_index_cpp vehicle_msgs)
set_target_properties(mujoco_sim_node PROPERTIES
    INSTALL_RPATH "${MUJOCO_DIR}/lib"
    BUILD_WITH_INSTALL_RPATH TRUE
)

install(TARGETS mujoco_sim_node DESTINATION lib/${PROJECT_NAME})
install(FILES model.xml DESTINATION share/${PROJECT_NAME})
ament_package()
