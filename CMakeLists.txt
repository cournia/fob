cmake_minimum_required( VERSION 2.8 )
project( libfob )

list( APPEND CMAKE_MODULE_PATH
  ${PROJECT_SOURCE_DIR}/CMake
  ${CMAKE_SOURCE_DIR}/CMake/common )

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif(NOT CMAKE_BUILD_TYPE)

if (CMAKE_BUILD_TYPE MATCHES "Debug")
  add_definitions(-DDEBUG)
endif()


# fob version
set( LAST_RELEASE 1.0.3 )
set( VERSION_MAJOR "1" )
set( VERSION_MINOR "0" )
set( VERSION_PATCH "3" )
set( VERSION_ABI 1 )

# description
set( FOB_DESCRIPTION "libfob is a C++ interface to Ascension Technology Corporation's Flock of Birds position and orientation measurement system." )
set( COMMON_PROJECT_DOMAIN https://github.com/cournia/fob )

if (MSVC)
	add_definitions(-DWIN32 -D_WIN32)
	find_package(GLM REQUIRED)
	find_package(Threads REQUIRED)
endif()

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

add_definitions(-DINCLUDE_EXAMPLE)
SET(INCLUDE_EXAMPLE TRUE CACHE BOOL "Setup the examples project")



add_subdirectory( fob )

if(INCLUDE_EXAMPLE)
	if (WIN32)
		find_package(FreeImage REQUIRED)
		find_package(GLUT REQUIRED)
		add_subdirectory( wtest )
	else()
		add_subdirectory( test )
	endif(WIN32)
endif(INCLUDE_EXAMPLE)


