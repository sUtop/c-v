project(server)

set(SERVER_SOURCES
    server.cpp
    messager.cpp
    generator.cpp)

add_executable(server ${SERVER_SOURCES}  ${QT_LIBRARIES}) 

target_link_libraries(server
    ${QT_LIBRARIES} 
    ${QT_QTCORE_LIBRARIES}
    ${QT_NETWORK_LIBRARIES})

qt5_use_modules(server Network)

