cmake_minimum_required(VERSION 3.8)
project(warehouse_automation)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclpy REQUIRED)
find_package(std_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)

find_package(sensor_msgs REQUIRED)
find_package(cv_bridge REQUIRED)
find_package(image_transport REQUIRED)



find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

# Took the below implementation and copied it from AWS_repository
find_package(gazebo_ros REQUIRED)



add_executable(talker src/publish_cmdvel.cpp)
ament_target_dependencies(talker rclcpp std_msgs geometry_msgs)

add_executable(mover src/velocity_publisher.cpp)
ament_target_dependencies(mover rclcpp std_msgs geometry_msgs)


add_executable(watcher src/camera_node.cpp)
ament_target_dependencies(watcher rclcpp std_msgs geometry_msgs sensor_msgs cv_bridge image_transport)

add_executable(lidar_control_node src/lidar_node.cpp)
ament_target_dependencies(lidar_control_node rclcpp std_msgs geometry_msgs sensor_msgs cv_bridge image_transport)


target_link_libraries(watcher ${OpenCV_LIBS})



install(
  DIRECTORY launch models worlds maps rviz
  DESTINATION share/${PROJECT_NAME}
)


install(TARGETS
  talker
  DESTINATION lib/${PROJECT_NAME})

  install(TARGETS
  mover
  DESTINATION lib/${PROJECT_NAME})

  install(TARGETS
  watcher
  DESTINATION lib/${PROJECT_NAME})
  
  install(TARGETS
  lidar_control_node
  DESTINATION lib/${PROJECT_NAME})





ament_environment_hooks("${CMAKE_CURRENT_SOURCE_DIR}/env-hooks/aws_robomaker_small_warehouse_world.dsv.in")
ament_export_dependencies(ament_cmake)
ament_export_dependencies(gazebo_ros)
# Took the above implementation and copied it from AWS_repository



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

ament_package()
