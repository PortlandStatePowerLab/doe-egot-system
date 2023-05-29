add_library(ecs_client_cta2045
  src/module.cpp
)

add_library(ecs::client::cta2045 ALIAS ecs_client_cta2045)

target_include_directories(ecs_client_cta2045 PUBLIC include)

target_link_libraries(ecs_client_cta2045 PUBLIC 
  flecs
  trust::client
  sep::models
  sep::xml
  cta2045::ucm
)