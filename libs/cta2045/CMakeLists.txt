add_library(cta2045_ucm
  src/module.cpp
)

add_library(cta2045::ucm ALIAS cta2045_ucm)

target_include_directories(cta2045_ucm PUBLIC include)

target_link_libraries(cta2045_ucm PUBLIC 
  flecs
  trust::client
  sep::models
  sep::xml
)