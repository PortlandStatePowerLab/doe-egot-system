# Find packages go here.
find_package(Boost REQUIRED)
find_package(OpenSSL REQUIRED)

FetchContent_Declare(
  flecs
  GIT_REPOSITORY https://github.com/SanderMertens/flecs.git
  GIT_TAG        v2.3.2
)

FetchContent_MakeAvailable(flecs)

# project dirs
add_subdirectory(src)