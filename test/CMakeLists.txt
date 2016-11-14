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

find_package(GLUT REQUIRED)
find_package(GLEW REQUIRED)
find_package(GLM REQUIRED)



set(TEST_LINK_LIBRARIES PUBLIC
  ${OPENGL_LIBRARIES}
  ${GLEW_LIBRARIES}
  ${GLUT_LIBRARIES}
)

add_executable(TEST ${TEST_SOURCES} ${TEST_PUBLIC_HEADERS} )

target_link_libraries(TEST PUBLIC
	FOB
    ${TEST_LINK_LIBRARIES}
)

target_include_directories(TEST PUBLIC
	${FOB_INCLUDE_DIR}
    ${GLEW_INCLUDE_DIRS}
)
