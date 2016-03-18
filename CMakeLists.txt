cmake_minimum_required(VERSION 3.0.0)

project(client-viewer)
# Добавление виртуальной цели
add_custom_target(client-viewer)

# Удаление папки бинарников
if (EXISTS "bin")
   file(REMOVE_RECURSE "bin")
endif()

# Установка путей по-умолчанию
set (ROOT_DIR ${PROJECT_SOURCE_DIR})

set (CMAKE_BINARY_DIR ${ROOT_DIR}/bin)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})


# Добавление системнозависимых определений
string(TOUPPER ${CMAKE_SYSTEM} U_SYSTEM)

if (${U_SYSTEM} MATCHES "LINUX")
    add_definitions(-std=c++11 -g -pthread)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ldl -lpthread -pthread -fPIC")
    find_package(Threads)
elseif (${U_SYSTEM} MATCHES "DARWIN")
    add_definitions(-std=c++11 -g -pthread)

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ldl -lpthread -pthread -fPIC")

elseif (${U_SYSTEM} MATCHES "WINDOWS")


endif (${U_SYSTEM} MATCHES "LINUX")

# Установки для Qt
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt5Core)
find_package(Qt5Gui)
find_package(Qt5OpenGL)
find_package(OpenGL)

###############  Подключение подпроекта server
add_subdirectory(server)

###############  Подключение подпроекта view
add_subdirectory(view)

# Добавление зависимостей для гарантии сборки подпроектов
add_dependencies(client-viewer server view)
