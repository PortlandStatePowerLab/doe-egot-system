add_executable(dcm_aosmith src/main.cpp)

target_link_libraries(dcm_aosmith cta2045::ucm EGoT::utils Threads::Threads)
