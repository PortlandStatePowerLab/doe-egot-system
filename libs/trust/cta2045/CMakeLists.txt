add_library(trust_cta2045 STATIC trust_ucm.cpp trust_device.cpp)

# Create ALIAS targets.
add_library(trust::cta2045 ALIAS trust_cta2045)

target_include_directories(trust_cta2045 PUBLIC include)

target_link_libraries(
  trust_cta2045 PUBLIC cta2045::device https::client trust_xml EGoT::utils
                       Threads::Threads)
