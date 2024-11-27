find_package(Boost REQUIRED)

add_library(trust_xml
    src/utils.cpp
)

add_library(trust::xml ALIAS trust_xml)

target_include_directories(trust_xml PUBLIC include)

target_link_libraries(trust_xml PUBLIC 
  Boost::boost
  sep::xml
)

