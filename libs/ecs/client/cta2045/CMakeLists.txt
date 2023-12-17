add_library(ecs_cta2045 src/ucm.cpp)

add_library(ecs::cta2045 ALIAS ecs_cta2045)

target_include_directories(ecs_cta2045 PUBLIC include)

target_link_libraries(ecs_cta2045 PUBLIC flecs trust::client sep::models
                                         sep::xml cta2045::ucm)
