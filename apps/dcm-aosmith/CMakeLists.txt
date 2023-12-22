add_executable(dcm_aosmith src/main.cpp)
target_link_libraries(dcm_aosmith trust::cta2045 ecs::cta2045 sep::models
                      EGoT::utils Threads::Threads)

add_executable(dcm_aosmith_test src/test.cpp)
target_link_libraries(dcm_aosmith_test trust::cta2045 ecs::cta2045 EGoT::utils
                      Threads::Threads)
