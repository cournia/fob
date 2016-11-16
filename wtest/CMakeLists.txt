source_group( \\ FILES CMakeLists.txt )

include_directories(${PROJECT_SOURCE_DIR})

set(WTEST_PUBLIC_HEADERS
	auxiliar.h
	BOX.h
)

set(WTEST_SOURCES
	auxiliar.cpp
	SerialConnection.cpp
)

set(WTEST_LINK_LIBRARIES PUBLIC
	${PTHREAD_LIBRARIES}
	${OPENGL_LIBRARIES}
	${GLEW_LIBRARIES}
	${GLUT_LIBRARIES}
	${FREEIMAGE_LIBRARIES}
	${GLEW_LIBRARIES}
)

add_executable(wtest ${WTEST_SOURCES} ${WTEST_PUBLIC_HEADERS} )


target_include_directories(wtest PUBLIC
	fob
	${FREEIMAGE_INCLUDE_DIRS}
	${ASSIMP_INCLUDE_DIR}
	${GLEW_INCLUDE_DIRS}
	${GLM_INCLUDE_DIR}
	${PTHREAD_INCLUDE_DIR}
)
target_link_libraries(wtest PUBLIC
	fob
	${WTEST_LINK_LIBRARIES}

)

