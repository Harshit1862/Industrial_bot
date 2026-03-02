cmake_minimum_required(VERSION 3.8)
project(my_cpp_pkg)

# Enable warnings
if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(example_interfaces REQUIRED)
find_package(my_robot_interfaces REQUIRED)

# -------------------------
# Executables
# -------------------------

# 1. Hardware Status Publisher (Uses my_robot_interfaces)
add_executable(hardware_status_publisher src/hardware_status_publisher.cpp)
ament_target_dependencies(hardware_status_publisher rclcpp my_robot_interfaces)

# 2. Robot News Station (Uses example_interfaces)
add_executable(robot_news_station src/robot_news_station.cpp)
ament_target_dependencies(robot_news_station rclcpp example_interfaces)

# 3. Smartphone (Uses example_interfaces)
add_executable(smartphone src/smartphone.cpp)
ament_target_dependencies(smartphone rclcpp example_interfaces)

# 4. Add Two Ints Server (Uses example_interfaces)
add_executable(add_two_ints_server src/add_two_ints_server.cpp)
ament_target_dependencies(add_two_ints_server rclcpp example_interfaces)

# 5. Add Two Ints Client (Uses example_interfaces)
add_executable(add_two_ints_client src/add_two_ints_client.cpp)
ament_target_dependencies(add_two_ints_client rclcpp example_interfaces)

# 6. Add Two Ints Client No OOP (Uses example_interfaces)
add_executable(add_two_ints_client_no_oop src/add_two_ints_client_no_oop.cpp)
ament_target_dependencies(add_two_ints_client_no_oop rclcpp example_interfaces)

# 7. Basic Publisher (Uses std_msgs)
add_executable(publisher_member_function src/publisher_member_function.cpp)
ament_target_dependencies(publisher_member_function rclcpp std_msgs)

# 8. Basic Subscriber (Uses std_msgs)
add_executable(subscriber_member_function src/subscriber_member_function.cpp)
ament_target_dependencies(subscriber_member_function rclcpp std_msgs)

# 9. Battery Publisher (Uses std_msgs - agar change kiya ho to bata dena)
add_executable(battery_pub src/battery_pub.cpp)
ament_target_dependencies(battery_pub rclcpp std_msgs)

# 10. Battery Subscriber (Uses std_msgs)
add_executable(battery_sub src/battery_sub.cpp)
ament_target_dependencies(battery_sub rclcpp std_msgs)

# 11. CPU Publisher (Uses std_msgs)
add_executable(cpu_pub src/cpu_pub.cpp)
ament_target_dependencies(cpu_pub rclcpp std_msgs)

# 12. CPU Subscriber (Uses std_msgs)
add_executable(cpu_sub src/cpu_sub.cpp)
ament_target_dependencies(cpu_sub rclcpp std_msgs)

# # 13. Counter Subscriber (Uses example_interfaces)
# add_executable(count_pub src/number_publisher.cpp)
# ament_target_dependencies(count_pub rclcpp example_interfaces)


# -------------------------
# Install targets
# -------------------------
install(TARGETS
  hardware_status_publisher
  robot_news_station
  smartphone
  add_two_ints_server
  add_two_ints_client
  add_two_ints_client_no_oop
  publisher_member_function
  subscriber_member_function
  battery_pub
  battery_sub
  cpu_pub
  cpu_sub
# count_pub
  DESTINATION lib/${PROJECT_NAME}
)

ament_package()