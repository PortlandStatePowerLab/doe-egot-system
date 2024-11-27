add_executable(dcm
    src/main.cpp
)

# target_include_directories(dcm PUBLIC include)

target_link_libraries(dcm
    ecs::client::sep
    ecs::simulator
    https::client
    trust::client
    EGoT::utils
    Threads::Threads
)