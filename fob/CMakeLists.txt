source_group( \\ FILES CMakeLists.txt )


if (WIN32)
	MESSAGE(STATUS "Windows detected" )
	set(FOB_HEADERS
		wfob.h
		rs232.h
	)

	find_package(GLM REQUIRED)
	find_package(PTHREAD REQUIRED)

	set(FOB_SOURCES
		wfob.cpp
		rs232.c
	)

	set(FOB_LINK_LIBRARIES PUBLIC
	${GLUT_LIBRARY}
	${PTHREAD_LIBRARY}
	)

else()

	MESSAGE(STATUS "No Windows detected" )
	set(FOB_HEADERS
		fob.h
		mathematics.h
		matrix.h
		quaternion.h
		vector.h
	)

	find_package(GLM REQUIRED)

	set(FOB_SOURCES
		fob.cpp
		mathematics.cpp
		matrix.cpp
		quaternion.cpp
		vector.cpp
	)

	

endif(WIN32)


add_library(FOB ${FOB_HEADERS} ${FOB_SOURCES})

target_include_directories(FOB PUBLIC
	${GLM_INCLUDE_DIR}
	${PTHREAD_INCLUDE_DIR}
)

target_link_libraries(FOB
	${FOB_LINK_LIBRARIES}
)
