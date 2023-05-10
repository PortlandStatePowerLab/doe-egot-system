add_executable(gsp
    src/main.cpp
)

target_link_libraries(gsp
    https::server 
    ecs::server::sep
    EGoT::utils
)