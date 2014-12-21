project(TileDL)
cmake_minimum_required(VERSION 2.8)

# Point to our own cmake modules
list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/CMake)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

# Match build folder structure to src
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR})

# Find Libraries
find_package(SDL2 REQUIRED)

add_definitions("-std=c++11")

include_directories(${SDL2_INCLUDE_DIR})
include_directories(${JSONCPP_INCLUDE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/src)

add_library(tiledl SHARED
	src/Timer.cpp
	src/Game.cpp
	src/Vector.cpp
	src/Point.cpp
	src/Rectangle.cpp
	src/Window.cpp
	src/Renderer.cpp
	src/Color.cpp
	src/Texture.cpp
	)

target_link_libraries(tiledl ${SDL2_LIBRARIES})
target_link_libraries(tiledl ${JSONCPP_LIBRARIES})

if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
	set(TILEDL_LIBRARY ${LIBRARY_OUTPUT_PATH}/libtiledl.dlll)
else()
	set(TILEDL_LIBRARY ${LIBRARY_OUTPUT_PATH}/libtiledl.so)
endif()

# Test Suite
find_package(UnitTest++ QUIET)
if (UNITTEST++_FOUND)
	enable_testing()

	add_executable(tiledlTest
		tests/VectorTest.cpp
		tests/GameTest.cpp
		tests/SanityTest.cpp
		tests/runner.cpp
		tests/RectangleTest.cpp
		tests/RendererTest.cpp
		tests/WindowTest.cpp
		tests/ColorTest.cpp
		tests/PointTest.cpp
		)
	add_dependencies(tiledlTest tiledl)

	include_directories(${UNITTEST++_INCLUDE_DIR})

	target_link_libraries(tiledlTest ${TILEDL_LIBRARY})
	target_link_libraries(tiledlTest ${SDL2_LIBRARIES})
	target_link_libraries(tiledlTest ${JSONCPP_LIBRARIES})
	target_link_libraries(tiledlTest ${UNITTEST++_LIBRARY})

	add_test(TileDLTest tiledlTest)
endif()

find_package(Doxygen)
if(DOXYGEN_FOUND)
	configure_file(${CMAKE_CURRENT_SOURCE_DIR}/doc/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
	add_custom_target(doc
		${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
		WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
		COMMENT "Generating API documentation with Doxygen" VERBATIM
		)
endif(DOXYGEN_FOUND)
