add_executable(dcm_aosmith src/main.cpp)

target_link_libraries(dcm_aosmith trust::cta2045 EGoT::utils Threads::Threads)
