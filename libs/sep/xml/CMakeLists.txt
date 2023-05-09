find_package(XercesC REQUIRED)
find_package(Boost REQUIRED)

add_library(sep_xml
    src/device_capability_adapter.cpp
    src/end_device_adapter.cpp
    src/flow_reservation_response_adapter.cpp
    src/flow_reservation_request_adapter.cpp
    src/power_status_adapter.cpp
    src/registration_adapter.cpp
    src/response_adapter.cpp
    src/response_set_adapter.cpp
    src/self_device_adapter.cpp
    src/time_adapter.cpp
    src/xml_validator.cpp
)

# Create ALIAS targets.
add_library(sep::xml ALIAS sep_xml)

target_include_directories(sep_xml PUBLIC include)

target_link_libraries(sep_xml PUBLIC
    sep::models 
    Boost::boost
    XercesC::XercesC
)

add_subdirectory(tests)