find_package(Boost REQUIRED filesystem)
find_package(OpenSSL REQUIRED)
find_package(Threads REQUIRED)

add_library(https_server STATIC
  src/server.cpp   
)

add_library(https::server ALIAS https_server)

target_include_directories(https_server PUBLIC include)

target_link_libraries(https_server PUBLIC
  Boost::boost
  Boost::filesystem
  OpenSSL::SSL
  Threads::Threads
  ecs::server::sep
  sep::models
  sep::wadl
  EGoT::utils
)