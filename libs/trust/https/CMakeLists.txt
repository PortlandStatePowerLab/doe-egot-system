find_package(Boost REQUIRED)

add_library(trust_client
  src/client.cpp
)

# Create ALIAS targets.
add_library(trust::client ALIAS trust_client)

target_include_directories(trust_client PUBLIC include)

target_link_libraries(trust_client PUBLIC 
  Boost::boost
  https::client
  EGoT::utils
  sep::models
  sep::xml
  trust::xml
)