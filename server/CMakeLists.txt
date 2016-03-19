project(server)

set(SERVER_SOURCES
    server.cpp
    messager.cpp
    generator.cpp)

add_executable(server ${SERVER_SOURCES} ) 

target_link_libraries(server
    ${QT_LIBRARIES} )

qt5_use_modules(server Network)

