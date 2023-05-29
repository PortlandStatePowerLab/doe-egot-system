find_package(XercesC REQUIRED)
find_package(Boost REQUIRED)
find_package(GTest REQUIRED)

add_executable(sep_xml_tests
    src/main.cpp
    src/dcap_tests.cpp
    src/sdev_tests.cpp
    src/edev_tests.cpp
    src/rg_tests.cpp
    src/dstat_tests.cpp
    src/fsa_tests.cpp
    src/frp_tests.cpp 
    src/frq_tests.cpp
    src/sub_tests.cpp
    src/ntfy_tests.cpp
    src/rsps_tests.cpp
    src/rsp_tests.cpp
    src/tm_tests.cpp
    src/ps_tests.cpp
)

target_compile_features(sep_xml_tests PRIVATE cxx_std_11)

target_link_libraries(sep_xml_tests PUBLIC
    sep::xml
    EGoT::utils
    Boost::boost
    XercesC::XercesC
    GTest::GTest
)