# You should always specify a range with the newest and oldest tested versions
# of CMake.
cmake_minimum_required(VERSION 3.18)

# This is your project statement. You should always list languages;
project(
  EGoT
  VERSION 0.1.0
  LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# fetch remote packages for development
find_package(Boost REQUIRED python filesystem)

find_package(Python3 COMPONENTS Interpreter Development)

include(FindThreads)

include(FindXercesC)

include(FindGTest)

include(FetchContent)
# toggle with previous set after first build to stop downloading and building
# fetched libs
set(FETCHCONTENT_UPDATES_DISCONNECTED=ON)
# set(FETCHCONTENT_FULLY_DISCONNECTED=ON)

FetchContent_Declare(
  flecs
  GIT_REPOSITORY https://github.com/SanderMertens/flecs.git
  GIT_TAG master)

FetchContent_Declare(
  cea2045
  GIT_REPOSITORY https://github.com/epri-dev/CTA-2045-UCM-CPP-Library.git
  GIT_TAG v1.0)

FetchContent_MakeAvailable(flecs cea2045)

add_subdirectory(libs)
add_subdirectory(apps)

# install resources for programs
execute_process(
  COMMAND ${CMAKE_COMMAND} -E copy_directory
          ${CMAKE_CURRENT_SOURCE_DIR}/resources/ ${CMAKE_BINARY_DIR}/bin/)

execute_process(
  COMMAND
    ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/ssl/root-ca/
    ${CMAKE_BINARY_DIR}/bin/root-ca/)
