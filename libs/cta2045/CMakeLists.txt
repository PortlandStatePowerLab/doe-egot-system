add_library(cta2045_ucm src/device.cpp src/ucm.cpp)

add_library(cta2045::ucm ALIAS cta2045_ucm)

target_include_directories(cta2045_ucm PUBLIC include
                                              ${cea2045_SOURCE_DIR}/cea2045)

target_link_libraries(cta2045_ucm PUBLIC flecs cea2045 trust::client
                                         sep::models sep::xml)
