find_package(Boost REQUIRED)

add_library(sep_models INTERFACE)

add_library(sep::models ALIAS sep_models)

target_include_directories(sep_models INTERFACE include)

target_link_libraries(sep_models INTERFACE Boost::boost)