source_group( \\ FILES CMakeLists.txt )

set(TEST_PUBLIC_HEADERS
	args.h
	camera.h
	commandoptions.h
	
)



set(TEST_SOURCES
	camera.cpp
	commandoptions.cpp
	fly2.cpp
)



set(TEST_LINK_LIBRARIES PUBLIC
  ${OPENGL_LIBRARIES}
  ${GLEW_LIBRARIES}
  ${GLUT_LIBRARIES}
  ${CMAKE_THREAD_LIBS_INIT}
)

include_directories(${PROJECT_SOURCE_DIR})

add_executable(test ${TEST_SOURCES} ${TEST_PUBLIC_HEADERS} )

target_link_libraries(test PUBLIC
	fob
	${TEST_LINK_LIBRARIES}
)

target_include_directories(test PUBLIC
	${FOB_INCLUDE_DIR}
	${GLEW_INCLUDE_DIRS}
)
