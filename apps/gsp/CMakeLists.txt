add_executable(gsp
    src/main.cpp
)

target_link_libraries(gsp
    https::server 
    https::client
    ecs::server::sep
    EGoT::utils
)

add_subdirectory(tests)