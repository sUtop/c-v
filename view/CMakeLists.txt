project(view)


set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

#string(TOUPPER ${CMAKE_SYSTEM} U_SYSTEM)
#
#if (${U_SYSTEM} MATCHES "LINUX")
#    add_definitions(-pthread)
#    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ldl -lpthread -pthread -fPIC")
#    find_package(Threads)
#elseif (${U_SYSTEM} MATCHES "DARWIN")
#    add_definitions(-std=c++11 -g -pthread)
#
#    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ldl -lpthread -pthread -fPIC")
#
#elseif (${U_SYSTEM} MATCHES "WINDOWS")
#
#
#endif (${U_SYSTEM} MATCHES "LINUX")



find_package(Qt5Core)
find_package(Qt5Gui)
find_package(Qt5OpenGL)
find_package(OpenGL)

set(VIEW_SOURCES
    view.cpp
    widget.cpp
    messager.cpp)

#include_directories("view")

add_executable(view ${VIEW_SOURCES})

target_link_libraries(view
    ${QT_LIBRARIES} 
    ${OPENGL_LIBRARIES})

qt5_use_modules(view PrintSupport Gui Core OpenGL)
