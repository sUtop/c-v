project(server)

set(SERVER_SOURCES
    server.cpp
    messager.cpp
    generator.cpp)

add_executable(server ${SERVER_SOURCES} ) 

