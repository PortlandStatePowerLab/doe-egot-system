add_library(ecs_singleton
  src/clock.cpp
)

# Create ALIAS targets.
add_library(ecs::singleton ALIAS ecs_singleton)

target_include_directories(ecs_singleton PUBLIC include)

target_link_libraries(ecs_singleton PUBLIC
  flecs::flecs
  EGoT::utils
) 