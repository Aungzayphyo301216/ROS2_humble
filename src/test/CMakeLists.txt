cmake_minimum_required(VERSION 3.8)
project(test)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(std_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(rclcpp REQUIRED)
find_package(tutorial_interfaces REQUIRED)

find_package(tf2_ros REQUIRED)
find_package(turtlesim REQUIRED)

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

add_executable(talker src/publisher_member_function.cpp)
ament_target_dependencies(talker rclcpp std_msgs)

add_executable(talker1 src/pub_custom.cpp)
ament_target_dependencies(talker1 rclcpp tutorial_interfaces)

add_executable(listener src/subscriber_member_function.cpp)
ament_target_dependencies(listener rclcpp std_msgs)

add_executable(listener1 src/sub_custom.cpp)
ament_target_dependencies(listener1 rclcpp tutorial_interfaces)

#for turtle_broadcaster
add_executable(turtle_broadcaster src/turtle_broadcaster.cpp)
ament_target_dependencies(
    turtle_broadcaster
    geometry_msgs
    rclcpp
    tf2
    tf2_ros
    turtlesim
)

#for turtle-lister
add_executable(turtle_tf2_listener src/turtle_tf2_listerner.cpp)
ament_target_dependencies(
    turtle_tf2_listener
    geometry_msgs
    rclcpp
    tf2
    tf2_ros
    turtlesim
)
#for add_fixed_frame
add_executable(fixed_frame_tf2_broadcaster src/add_fixed_frame.cpp)
ament_target_dependencies(
    fixed_frame_tf2_broadcaster
    geometry_msgs
    rclcpp
    tf2_ros
)
install(TARGETS
    fixed_frame_tf2_broadcaster
    DESTINATION lib/${PROJECT_NAME}
)

#for dynamic_tf2_broadcaster

add_executable(dynamic_frame_tf2_broadcaster src/dynamic_frame.cpp)
ament_target_dependencies(
    dynamic_frame_tf2_broadcaster
    geometry_msgs
    rclcpp
    tf2_ros
)
install(TARGETS
    dynamic_frame_tf2_broadcaster
    DESTINATION lib/${PROJECT_NAME}
)


install(TARGETS
turtle_broadcaster
talker
listener
talker1
listener1
turtle_tf2_listener

DESTINATION lib/${PROJECT_NAME}
)

install(DIRECTORY
	launch
	DESTINATION share/${PROJECT_NAME}
)


ament_package()
