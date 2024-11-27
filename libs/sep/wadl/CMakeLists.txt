find_package(Boost REQUIRED)

add_library(sep_wadl
    src/wadl.cpp
)

add_library(sep::wadl ALIAS sep_wadl)

target_include_directories(sep_xml PUBLIC include)

target_link_libraries(sep_wadl 
    EGoT::utils
    sep::xml
    Boost::boost
    XercesC::XercesC
)