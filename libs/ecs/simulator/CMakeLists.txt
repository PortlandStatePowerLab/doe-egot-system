add_library(ecs_simulator
  src/waterheater.cpp
)

# Create ALIAS targets.
add_library(ecs::simulator ALIAS ecs_simulator)

target_include_directories(ecs_simulator PUBLIC include)

target_link_libraries(ecs_simulator PUBLIC
  flecs::flecs
  https::client
  ecs::singleton
  sep::models
  sep::xml
  EGoT::utils
) 