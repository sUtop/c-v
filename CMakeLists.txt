cmake_minimum_required(VERSION 3.0.0)


if (EXISTS "bin")
   file(REMOVE_RECURSE "bin")
endif()

add_definitions(-std=c++11 -g)



project(server)

set (ROOT_DIR ${PROJECT_SOURCE_DIR})

set (CMAKE_BINARY_DIR ${ROOT_DIR}/bin)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})


string(TOUPPER ${CMAKE_SYSTEM} U_SYSTEM)

if (${U_SYSTEM} MATCHES "LINUX")
    add_definitions(-pthread)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ldl -lpthread -pthread -fPIC")
    find_package(Threads)

endif (${U_SYSTEM} MATCHES "LINUX")





set(SERVER_SOURCES
    server/server.cpp
    server/messager.cpp
    server/generator.cpp)

add_executable(server ${SERVER_SOURCES} ) 





project(viewer)


set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

# if Darwin - path to qt
#set (PATH "${PATH}:/usr/local/Qt-5.5.0/")

string(TOUPPER ${CMAKE_SYSTEM} U_SYSTEM)

if (${U_SYSTEM} MATCHES "LINUX")
    add_definitions(-pthread)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ldl -lpthread -pthread -fPIC")
    find_package(Threads)

endif (${U_SYSTEM} MATCHES "LINUX")



find_package(Qt5Core)
find_package(Qt5Gui)
find_package(Qt5OpenGL)
find_package(OpenGL)

set(VIEW_SOURCES
    view/view.cpp
    view/widget.cpp
    view/messager.cpp)

include_directories("view")

add_executable(viewer ${VIEW_SOURCES})

target_link_libraries(viewer
    ${QT_LIBRARIES} 
    ${OPENGL_LIBRARIES})

qt5_use_modules(viewer PrintSupport Gui Core OpenGL)


