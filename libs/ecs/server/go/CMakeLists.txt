find_package(OpenSSL REQUIRED)
find_package(Threads REQUIRED)

add_library(topology.cpp energy.cpp reserve.cpp regulation.cpp emergency.cpp
                         voltage.cpp frequency.cpp)

# Create ALIAS targets.
add_library(ecs::server::go ALIAS ecs_server_go)

target_include_directories(ecs_server_go PUBLIC include)

target_link_libraries(
  ecs_server_go
  PUBLIC Boost::boost
         OpenSSL::SSL
         Threads::Threads
         flecs::flecs
         sep::models
         sep::xml
         ecs::singleton
         EGoT::utils)
