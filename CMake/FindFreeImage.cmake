# Try to find the FreeImage library and include path.
# Once done this will define
#
# FREEIMAGE_FOUND
# FREE_IMAGE_INCLUDE_DIR
# FREEIMAGE_LIBRARY
# 

IF (WIN32)
	FIND_PATH( FREEIMAGE_INCLUDE_DIR FreeImage.h
		${PROJECT_SOURCE_DIR}/extern/FreeImage
		DOC "The directory where FreeImage.h resides")
	FIND_LIBRARY( FREEIMAGE_LIBRARY freeimage
		PATHS
		${PROJECT_SOURCE_DIR}/FreeImage
		DOC "The FreeImage library")
ELSE (WIN32)
	FIND_PATH( FREEIMAGE_INCLUDE_DIR FreeImage.h
		/usr/include
		/usr/local/include
		/sw/include
		/opt/local/include
		DOC "The directory where FreeImage.h resides")
	FIND_LIBRARY( FREEIMAGE_LIBRARY freeimage
		PATHS
		/usr/lib64
		/usr/lib
		/usr/local/lib64
		/usr/local/lib
		/sw/lib
		/opt/local/lib
		DOC "The FreeImage library")
ENDIF (WIN32)

SET(FREEIMAGE_FOUND FALSE)
IF (FREEIMAGE_INCLUDE_DIR AND FREEIMAGE_LIBRARY)
  SET(FREEIMAGE_FOUND TRUE)
ENDIF(FREEIMAGE_INCLUDE_DIR AND FREEIMAGE_LIBRARY)

SET(FREEIMAGE_LIBRARIES ${FREEIMAGE_LIBRARY})
SET(FREEIMAGE_INCLUDE_DIRS ${FREEIMAGE_INCLUDE_DIR})


include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(FreeImage DEFAULT_MSG FREEIMAGE_LIBRARY FREEIMAGE_INCLUDE_DIR)

MARK_AS_ADVANCED(
	FREEIMAGE_FOUND 
	FREEIMAGE_LIBRARY
	FREE_IMAGE_INCLUDE_DIR)