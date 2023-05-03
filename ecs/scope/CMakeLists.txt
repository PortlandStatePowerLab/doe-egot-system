set(COMPONENT_NAME ecs_scope_demo)

add_executable(${COMPONENT_NAME}
	main.cpp
)

target_link_libraries(${COMPONENT_NAME}
	flecs
	pthread
)

target_include_directories(${COMPONENT_NAME} PUBLIC
	${flecs_INCLUDE_DIRS}
)