find_package(Boost REQUIRED filesystem)
find_package(OpenSSL REQUIRED)
find_package(Threads REQUIRED)

add_library(
  ecs_server_sep
  src/rg.cpp
  src/dcap.cpp
  src/edev.cpp
  src/rsp.cpp
  src/sdev.cpp
  src/ps.cpp
  src/time.cpp
  src/world.cpp
  src/frq.cpp
  src/frp.cpp)

# Create ALIAS targets.
add_library(ecs::server::sep ALIAS ecs_server_sep)

target_include_directories(ecs_server_sep PUBLIC include)

target_link_libraries(
  ecs_server_sep
  PUBLIC Boost::boost
         Boost::filesystem
         OpenSSL::SSL
         Threads::Threads
         flecs::flecs
         sep::models
         sep::xml
         ecs::singleton
         https::client
         EGoT::utils)
