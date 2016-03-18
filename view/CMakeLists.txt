project(view)

set(VIEW_SOURCES
    view.cpp
    widget.cpp
    messager.cpp)

add_executable(view ${VIEW_SOURCES})

target_link_libraries(view
    ${QT_LIBRARIES} 
    ${OPENGL_LIBRARIES})

qt5_use_modules(view PrintSupport Gui Core OpenGL Network)
