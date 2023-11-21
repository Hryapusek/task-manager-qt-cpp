cmake_minimum_required(VERSION 3.10)
project(task_manager LANGUAGES CXX)
find_package(Qt5 COMPONENTS Widgets REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(target task_manager)

cmake_policy(SET CMP0076 NEW)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(build_test_executable OFF)

add_executable(${target})
target_include_directories(${target} PUBLIC src ${Qt5Widgets_INCLUDE_DIRS})
target_link_libraries(${target} PUBLIC Qt5::Widgets)

if (build_test_executable)
  set(test_target test_target)
  add_executable(${test_target})
  target_include_directories(${test_target} PUBLIC src ${Qt5Widgets_INCLUDE_DIRS})
  target_link_libraries(${test_target} PUBLIC Qt5::Widgets)
endif()

add_subdirectory(src)
