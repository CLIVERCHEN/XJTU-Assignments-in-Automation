cmake_minimum_required(VERSION 3.24)

project(MiniDraw)

set(CMAKE_PREFIX_PATH D:/Qt/6.4.0/msvc2019_64)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)

set(CMAKE_AUTOUIC ON)

SET(CMAKE_AUTORCC ON)

find_package(Qt5 REQUIRED COMPONENTS Core Widgets Gui)

set(project_ui 
	viewwidget.ui 
	MiniDraw.ui)

set(project_headers 
	MiniDraw.h 
	viewwidget.h 
	Shape.h Line.h 
	Free_Line.h 
	Rectangle.h 
	Polygon.h 
	Circle.h 
	Elliptical.h 
	Bezier_Curve.h 
	Eraser.h)

set(project_sources 
	main.cpp 
	MiniDraw.cpp 
	viewwidget.cpp 
	Shape.cpp 
	Line.cpp 
	Free_Line.cpp 
	Rectangle.cpp 
	Polygon.cpp 
	Circle.cpp 
	Elliptical.cpp 
	Bezier_Curve.cpp 
	Eraser.cpp)

set(project_resources 
	MiniDraw.qrc)

QT5_WRAP_UI(ui_files ${project_ui})

add_executable(${PROJECT_NAME} 
	${project_sources} 
	${project_headers} 
	${project_resources} 
	${ui_files})

target_link_libraries(${PROJECT_NAME}
	PUBLIC
	Qt5::Core
	Qt5::Gui
	Qt5::Widgets)