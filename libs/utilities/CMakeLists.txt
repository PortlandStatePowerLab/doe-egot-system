add_library(egot_utils
  src/utilities.cpp
)

# Create ALIAS targets.
add_library(${CMAKE_PROJECT_NAME}::utils ALIAS egot_utils)

target_include_directories(egot_utils PUBLIC include)

target_link_libraries(egot_utils PUBLIC Boost::filesystem)