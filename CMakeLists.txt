cmake_minimum_required(VERSION 3.0)
project(ETSIDILib)
SET(srcdir "${CMAKE_CURRENT_SOURCE_DIR}/src")
SET(libdir "${CMAKE_CURRENT_SOURCE_DIR}/external")
SET(outdir "${CMAKE_CURRENT_SOURCE_DIR}/lib")
message("EL SRCDIR ES ${srcdir}")

INCLUDE_DIRECTORIES(${srcdir}/oglft) 

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
message("Contenido define_property ${CMAKE_GENERATOR_PLATFORM}")
if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    SET(libsubdir "x64")
elseif(CMAKE_SIZEOF_VOID_P EQUAL 4)
    SET(libsubdir "x86")
endif()


# ETSIDI library
ADD_LIBRARY(ETSIDI SHARED ${SOURCES} ${HEADERS} )

target_link_libraries( ETSIDI ${OPENGL_LIBRARIES} ${libdir}/${libsubdir}/fmodL_vc.lib)
 
target_link_libraries( ETSIDI debug ${libdir}/${libsubdir}/freetype.lib)
target_link_libraries( ETSIDI optimized  ${libdir}/${libsubdir}/freetype.lib)
IF(MSVC_VERSION GREATER_EQUAL 1900 )
	message("FIX for the Visual Studio (after VS2015) inline stdio functions")
	target_link_libraries( ETSIDI debug legacy_stdio_definitions.lib)
	target_link_libraries( ETSIDI optimized legacy_stdio_definitions.lib)
ENDIF()
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
    COMMAND ${CMAKE_COMMAND} -E copy ${libdir}/${libsubdir}/fmodL.dll  ${CMAKE_CURRENT_SOURCE_DIR}/lib
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