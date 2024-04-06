cmake_minimum_required(VERSION 3.25) 

project(ogc)

add_executable(ogc main.c)

find_package(OpenGL REQUIRED)

add_subdirectory(deps/glfw-3.4)
add_subdirectory(deps/glad)
add_subdirectory(deps/dbuf)

target_link_libraries(ogc glfw glad dbuf OpenGL::GL)
target_include_directories(ogc 
	PUBLIC ${PROJECT_SOURCE_DIR}/deps/glfw-3.4/include 
	PUBLIC ${PROJECT_SOURCE_DIR}/deps/glad/include
	PUBLIC ${PROJECT_SOURCE_DIR}/deps/dbuf/include
)

configure_file(
		shaders/shader.vert
		shaders/shader.vert
		COPYONLY
		)
configure_file(
		shaders/shader.frag
		shaders/shader.frag
		COPYONLY
		)
