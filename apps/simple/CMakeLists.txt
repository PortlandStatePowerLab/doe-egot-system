add_executable(simple src/main.cpp)

# target_include_directories(dcm PUBLIC include)

target_link_libraries(simple flecs Threads::Threads)
