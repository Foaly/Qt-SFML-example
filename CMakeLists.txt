cmake_minimum_required(VERSION 3.3)
project(Qt_SFML_example)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# Define sources and executable
set(EXECUTABLE_NAME "Qt_SFML_example")
set(SOURCE_FILES main.cpp
                 MainWindow.cpp
                 SFMLWidget.cpp)
add_executable(${EXECUTABLE_NAME} ${SOURCE_FILES})


# Detect and add SFML
set(SFML_ROOT "F:/Librarys/official_SFML/install")
set(CMAKE_MODULE_PATH "${SFML_ROOT}/cmake/modules" ${CMAKE_MODULE_PATH})
#Find any version 2.X of SFML
#See the FindSFML.cmake file for additional details and instructions
find_package(SFML 2 COMPONENTS system window graphics network audio REQUIRED)
if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES})
endif()


# Detect and add Qt
set(QT_ROOT "C:/Qt/5.4/mingw491_32")
set(CMAKE_PREFIX_PATH "${QT_ROOT}/lib/cmake" ${CMAKE_PREFIX_PATH})
# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

# Find the QtWidgets library
find_package(Qt5Widgets REQUIRED)

# Use the Widgets module from Qt 5.
target_link_libraries(${EXECUTABLE_NAME} Qt5::Widgets)
