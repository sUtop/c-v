project(view)

set(VIEW_SOURCES
    view.cpp
    widget.cpp
    messager.cpp)

add_executable(view ${VIEW_SOURCES} ${QT_LIBRARIES})

target_link_libraries(view
    ${QT_LIBRARIES}
    ${QT_QTCORE_LIBRARIES}
	${QT_NETWORK_LIBRARIES}
    ${OPENGL_LIBRARIES})

qt5_use_modules(view PrintSupport Gui Core OpenGL Network)
