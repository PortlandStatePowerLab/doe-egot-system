add_library(cta2045_device src/device.cpp src/ucm.cpp)

add_library(cta2045::device ALIAS cta2045_device)

target_include_directories(cta2045_device PUBLIC include
                                                 ${cea2045_SOURCE_DIR}/cea2045)

target_link_libraries(cta2045_device PUBLIC EGoT::utils cea2045)
