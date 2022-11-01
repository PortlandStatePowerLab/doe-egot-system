# Find packages go here.
find_package(Boost REQUIRED)
find_package(OpenSSL REQUIRED)

add_subdirectory(client)
add_subdirectory(server)
add_subdirectory(tests)
add_subdirectory(scale)