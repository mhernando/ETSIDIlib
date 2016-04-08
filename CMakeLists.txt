cmake_minimum_required(VERSION 3.0)

SET(srcdir "${CMAKE_CURRENT_SOURCE_DIR}/src")
SET(libdir "${CMAKE_CURRENT_SOURCE_DIR}/external")
SET(outdir "${CMAKE_CURRENT_SOURCE_DIR}/lib")
message("EL SRCDIR ES ${srcdir}")

#INCLUDE_DIRECTORIES(${curdir}/include) 

find_package(OpenGL REQUIRED)

####################################################################################################
# Iterate over children, creating SOURCE_GROUPs 
####################################################################################################
FILE(GLOB children RELATIVE ${srcdir} ${srcdir}/*)
SET(SOURCES "") 
SET(HEADERS "")
    FILE(GLOB_RECURSE child_sources ${srcdir}/*.cpp) 
    FILE(GLOB_RECURSE child_headers ${srcdir}/*.h)
    SET(SOURCES ${SOURCES} ${child_sources})
    SET(HEADERS ${HEADERS} ${child_headers})
FOREACH(child ${children})
IF(IS_DIRECTORY ${srcdir}/${child})
    FILE(GLOB_RECURSE child_sources ${srcdir}/${child}/*.cpp) 
    FILE(GLOB_RECURSE child_headers ${srcdir}/${child}/*.h)
    SET(SOURCES ${SOURCES} ${child_sources})
    SET(HEADERS ${HEADERS} ${child_headers})
    SOURCE_GROUP(${child} FILES ${child_sources} ${child_headers}) 
ENDIF()
ENDFOREACH()

# ETSIDI library
ADD_LIBRARY(ETSIDI SHARED ${SOURCES} ${HEADERS} )

target_link_libraries( ETSIDI ${OPENGL_LIBRARIES} ${libdir}/fmodL_vc.lib)
 
target_link_libraries( ETSIDI debug ${libdir}/freetype263d.lib)
target_link_libraries( ETSIDI optimized  ${libdir}/freetype263.lib)
set_target_properties(ETSIDI  PROPERTIES OUTPUT_NAME ETSIDI)
set_target_properties( ETSIDI PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${outdir}")
set_target_properties( ETSIDI PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${outdir}")
set_target_properties( ETSIDI PROPERTIES LIBRARY_OUTPUT_DIRECTORY_DEBUG "${outdir}" )
set_target_properties( ETSIDI PROPERTIES LIBRARY_OUTPUT_DIRECTORY_RELEASE "${outdir}" )
add_custom_command(TARGET ETSIDI POST_BUILD
   COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:ETSIDI>  ${outdir}
)
   
#SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${outdir})

#set_target_properties(ETSIDI  PROPERTIES DEBUG_OUTPUT_NAME ETSIDI_d)

add_custom_command(TARGET ETSIDI POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy ${libdir}/fmodL.dll  ${CMAKE_CURRENT_SOURCE_DIR}/lib
)


FILE(READ "${srcdir}/ETSIDI.h" CONTENTS)
file(WRITE "${outdir}/ETSIDI.h" 
"
#define USE_ETSIDI
#pragma comment(lib,\"ETSIDI.lib\")
//Cabecera Publica de ETSIDI. GENERADA AUTOMATICAMENTE
//#ifdef _DEBUG
//#pragma comment(lib,\"lib/ETSIDI_d.lib\")
//#else
//#pragma comment(lib,\"lib/ETSIDI.lib\")
//#endif

")
file(APPEND "${outdir}/ETSIDI.h" "${CONTENTS}")

ADD_SUBDIRECTORY(example)