cmake_minimum_required(VERSION 3.8)
project(executor)

if(NOT CMAKE_CXX_STANDART)
  set(CMAKE_CXX_STANDART 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(nav_msgs REQUIRED)

add_executable(thread src/multithread.cpp)
ament_target_dependencies(thread rclcpp std_msgs nav_msgs)

ament_package()
