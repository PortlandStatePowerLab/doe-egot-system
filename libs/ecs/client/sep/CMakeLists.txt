add_library(ecs_client_sep
  src/dcap.cpp
  src/edev.cpp
  src/rg.cpp
  src/tm.cpp
  # src/frq.cpp
  # src/frp.cpp
  # src/rsp.cpp
  # src/rsps.cpp
  # src/ps.cpp
)

add_library(ecs::client::sep ALIAS ecs_client_sep)

target_include_directories(ecs_client_sep PUBLIC include)

target_link_libraries(ecs_client_sep PUBLIC 
  flecs
  trust::client
  sep::models
  sep::xml
)