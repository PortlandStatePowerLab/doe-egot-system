add_library(https_client
  src/client.cpp
  src/single_client.cpp
)

# Create ALIAS targets.
add_library(https::client ALIAS https_client)

target_include_directories(https_client PUBLIC include)

target_link_libraries(https_client PUBLIC 
  Boost::boost
  OpenSSL::SSL
  sep::models
  sep::xml
)