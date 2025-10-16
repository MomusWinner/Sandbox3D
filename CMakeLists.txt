cmake_minimum_required(VERSION 3.16)
project(Sandbox3D)

# set the output directory for built objects.
# This makes sure that the dynamic library goes into the build directory automatically.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

add_subdirectory(third_party/raylib EXCLUDE_FROM_ALL)

add_executable(
	${PROJECT_NAME}

	src/main.cpp
	src/world.cpp
	src/character_controller.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/include
	${CMAKE_CURRENT_SOURCE_DIR}/third_party/raygui/src/
)

target_link_libraries(${PROJECT_NAME} PRIVATE raylib)
