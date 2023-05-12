find_package(GTest REQUIRED)
find_package(Threads REQUIRED)
find_package(Boost REQUIRED filesystem)

add_executable (gsp_tests
    src/main.cpp
    src/dcap_tests.cpp
    # src/sdev_tests.cpp
    # src/edev_tests.cpp
    # src/edev_list_tests.cpp
    # src/frp_list_tests.cpp 
    # src/frp_tests.cpp 
    # src/frq_list_tests.cpp 
    # src/frq_tests.cpp 
    # src/rg_tests.cpp
    # src/dstat_tests.cpp
    # src/fsa_tests.cpp
    # src/sub_tests.cpp
    # src/ntfy_tests.cpp
    # src/rsp_tests.cpp
    # src/rsps_tests.cpp
    # src/tm_tests.cpp
)

target_include_directories(gsp_tests PUBLIC include)

target_link_libraries(gsp_tests
    GTest::GTest
    Threads::Threads
    Boost::boost
    Boost::filesystem
    https::server 
    https::client
    sep::xml
    ecs::server::sep
    EGoT::utils
)
