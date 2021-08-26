include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        master
)

FetchContent_Declare(
  flecs
  GIT_REPOSITORY https://github.com/SanderMertens/flecs.git
  GIT_TAG        v2.3.2
)

FetchContent_MakeAvailable(googletest flecs)

add_executable (dcm_tests
    main.cpp
    random.cpp
    dcm_test.cpp
)

target_link_libraries(dcm_tests gtest gtest_main Model XML flecs pthread)
target_include_directories(
    dcm_tests PUBLIC 
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
    ${flecs_INCLUDE_DIRS}
    ${googletest_INCLUDE_DIRS}
)
