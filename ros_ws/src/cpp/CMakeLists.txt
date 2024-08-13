cmake_minimum_required(VERSION 3.8)
project(cpp)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(nav_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(custom_interface REQUIRED)
find_package(std_srvs REQUIRED)

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


add_executable(simple_node src/simple.cpp)
add_executable(publisher_node src/publisher.cpp)
add_executable(publisher_composition_node src/publisher_composition.cpp)
add_executable(move_robot_node src/move_robot.cpp)
add_executable(subscriber_node src/subscriber.cpp)
add_executable(read_odom src/read_odom.cpp)
add_executable(robot_age_node src/publish_robot_age.cpp)
add_executable(avoid_obstacle_node src/avoid_obstacles_with_laser.cpp)
add_executable(executor_minimal_node src/executor_minimal.cpp)
add_executable(executor_with_callback_node src/executor_with_callback.cpp)
add_executable(executor_with_2callback_node src/executor_with_2callbacks.cpp)
add_executable(multi_thread_executor_node src/multi_thread_executor.cpp)
add_executable(seperate_executors_node src/seperate_executors.cpp)
add_executable(callback_group_2timer_node src/callback_group_2timer.cpp)
add_executable(callback_group_reentrant_node src/callback_group_reentrants.cpp)
add_executable(callback_group_MutuallyExclusive_node src/callback_group_MutuallyExclusive.cpp)
add_executable(callback_group_MutuallyExclusiveMultiple_node src/callback_group_MutuallyExclusive_multiple.cpp)

ament_target_dependencies(simple_node rclcpp)
ament_target_dependencies(publisher_node rclcpp std_msgs)
ament_target_dependencies(publisher_composition_node rclcpp std_msgs)
ament_target_dependencies(move_robot_node rclcpp std_msgs geometry_msgs)
ament_target_dependencies(subscriber_node rclcpp std_msgs)
ament_target_dependencies(read_odom rclcpp nav_msgs)
ament_target_dependencies(robot_age_node rclcpp std_msgs custom_interface)
ament_target_dependencies(avoid_obstacle_node rclcpp std_msgs sensor_msgs geometry_msgs)
ament_target_dependencies(executor_minimal_node rclcpp)
ament_target_dependencies(executor_with_callback_node rclcpp nav_msgs)
ament_target_dependencies(executor_with_2callback_node rclcpp nav_msgs)
ament_target_dependencies(multi_thread_executor_node rclcpp nav_msgs) 
ament_target_dependencies(seperate_executors_node rclcpp nav_msgs) 
ament_target_dependencies(callback_group_2timer_node rclcpp) 
ament_target_dependencies(callback_group_reentrant_node rclcpp) 
ament_target_dependencies(callback_group_MutuallyExclusive_node rclcpp) 
ament_target_dependencies(callback_group_MutuallyExclusiveMultiple_node rclcpp) 

install(TARGETS
simple_node
publisher_node
publisher_composition_node
move_robot_node
subscriber_node
read_odom
robot_age_node
avoid_obstacle_node
executor_minimal_node
executor_with_callback_node
executor_with_2callback_node
multi_thread_executor_node
seperate_executors_node
callback_group_2timer_node
callback_group_reentrant_node
callback_group_MutuallyExclusive_node
callback_group_MutuallyExclusiveMultiple_node
DESTINATION lib/${PROJECT_NAME}
)
install(DIRECTORY
launch
DESTINATION share/${PROJECT_NAME}/
)
ament_package()
