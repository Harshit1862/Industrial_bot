cmake_minimum_required(VERSION 3.8)
project(yaml_comm_pkg)

# Default to C++14 (Standard for ROS 2 Humble/Galactic)
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(yaml-cpp REQUIRED)

# 1. Publisher Executable
add_executable(yaml_publisher src/yaml_publisher.cpp)
ament_target_dependencies(yaml_publisher rclcpp std_msgs)
target_link_libraries(yaml_publisher yaml-cpp)

# 2. Subscriber Executable
add_executable(yaml_subscriber src/yaml_subscriber.cpp)
ament_target_dependencies(yaml_subscriber rclcpp std_msgs)
target_link_libraries(yaml_subscriber yaml-cpp)

# Install the executables so 'ros2 run' can find them
install(TARGETS
  yaml_publisher
  yaml_subscriber
  DESTINATION lib/${PROJECT_NAME}
)

ament_package()