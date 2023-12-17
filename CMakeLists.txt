cmake_minimum_required(VERSION 3.10)

project(task_manager LANGUAGES CXX)

include(conan_toolchain.cmake)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(target task_manager)

cmake_policy(SET CMP0076 NEW)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets Core LinguistTools REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets Core LinguistTools REQUIRED)
if (Qt${QT_VERSION_MAJOR} STREQUAL Qt6)
  qt6_create_translation(TR_FILES ${CMAKE_SOURCE_DIR} translations/rus.ts)
elseif(Qt${QT_VERSION_MAJOR} STREQUAL Qt5)
  qt5_create_translation(TR_FILES ${CMAKE_SOURCE_DIR} translations/rus.ts)
endif()

option(build_test_executable OFF)

add_executable(${target})
target_include_directories(${target} PUBLIC src)
target_link_libraries(${target} PUBLIC Qt${QT_VERSION_MAJOR}::Widgets)
target_sources(${target} PRIVATE ${TR_FILES})

file(GLOB_RECURSE style_files styles/*.qss)
message("Found style files ${style_files}")
file(COPY ${style_files} DESTINATION ${CMAKE_BINARY_DIR}/styles)

if (build_test_executable)
  set(test_target test_target)
  add_executable(${test_target})
  target_include_directories(${test_target} PUBLIC src)
  target_link_libraries(${test_target} PUBLIC Qt${QT_VERSION_MAJOR}::Widgets)
endif()

add_subdirectory(src)
