project(kongomato)
cmake_minimum_required(VERSION 2.8)
add_definitions(-ggdb)

find_package(OpenGL REQUIRED)
find_package(Qt4 COMPONENTS QtOpenGL REQUIRED)
find_package(SDL)
find_package(SDL_image)

set(SUPPORT_3DS TRUE CACHE BOOL "Support 3ds file format")

if(NOT QT_QTOPENGL_FOUND AND NOT SDLIMAGE_FOUND)
    MESSAGE( FATAL_ERROR "At least one of this library must be installed: Qt4 (with OpenGL module) or SDL (with SDL_image)")
endif()


set(LINK_DIRS ${CMAKE_CURRENT_SOURCE_DIR})
set(INCLUDE_DIRS "")
set(GLOBAL_DEFS "")

set(KONGOMATO_CPPS kongobase.cpp kongomath.cpp kongovideodevice.cpp kongoscene.cpp kongofileformat.cpp 3rd_party/GLee/GLee.c
		   kongosprite.cpp kongofont.cpp kongowidgets.cpp kongoscene2d.cpp
		   kongoinput.cpp)
set(KONGOMATO_LINK_LIBS ${KONGOMATO_LINK_LIBS} ${OPENGL_gl_LIBRARY})

if(SUPPORT_3DS AND NOT WIN32)
    set(KONGOMATO_LINK_LIBS ${KONGOMATO_LINK_LIBS} 3ds)
    add_definitions(-DSUPPORT_3DS)
elseif(SUPPORT_3DS AND WIN32)
	set(KONGOMATO_CPPS ${KONGOMATO_CPPS} 
		../lib3ds/atmosphere.c 
		../lib3ds/background.c
		../lib3ds/camera.c
		../lib3ds/chunk.c
		../lib3ds/ease.c
		../lib3ds/file.c 
		../lib3ds/io.c 
		../lib3ds/light.c
		../lib3ds/material.c
		../lib3ds/matrix.c
		../lib3ds/mesh.c 
		../lib3ds/node.c
		../lib3ds/quat.c
		../lib3ds/shadow.c
		../lib3ds/tcb.c
		../lib3ds/tracks.c
		../lib3ds/vector.c
		../lib3ds/viewport.c)
        set(INCLUDE_DIRS ${INCLUDE_DIRS}  ../lib3ds ../)
	add_definitions(-DSUPPORT_3DS)
endif()

set(TEST_CPPS test.cpp kongoapplication.cpp) 
set(TEST_LINK_LIBS kongomato)
set(BUILD_TEST SDL_FOUND)

set(TEST2D_CPPS test2d.cpp kongoapplication.cpp) 
set(TEST2D_LINK_LIBS kongomato)
set(BUILD_TEST2D SDL_FOUND)

if(WIN32)
    if(MSVC)
	set(GLOBAL_DEFS ${GLOBAL_DEFS} -D_USE_MATH_DEFINES)
    else()
	set(WIN32_MINGW_LIBS mingw32)
    endif()
    if(SDL_FOUND) 
	set(WIN32_MINGW_LIBS ${MINGW_WIN32_LIBS} ${SDMAIN_LIBRARY})
    endif()
    set(TEST_LINK_LIBS ${TEST_LINS_LIBS} ${MINGW_WIN32_LIBS})
    set(TEST2D_LINK_LIBS ${TEST2D_LINK_LIBS} ${MINGW_WIN32_LIBS})
endif()

if( CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64" )
	set(GLOBAL_DEFS ${GLOBAL_DEFS} -fPIC)
endif()

if(QT_QTOPENGL_FOUND)    
    set(GLOBAL_DEFS ${GLOBAL_DEFS} -DWITH_QT4)
    QT4_WRAP_CPP(moc_kongomato kongovideodevice.h OPTIONS -DWITH_QT4)
    set(INCLUDE_DIRS ${INCLUDE_DIRS} ${QT_INCLUDE_DIR})
    set(KONGOMATO_LINK_LIBS ${KONGOMATO_LINK_LIBS} ${QT_QTOPENGL_LIBRARY} ${QT_QTGUI_LIBRARY} ${QT_QTCORE_LIBRARY})
    set(KONGOMATO_CPPS ${KONGOMATO_CPPS} ${moc_kongomato})
endif()

if(SDL_FOUND)
    set(GLOBAL_DEFS ${GLOBAL_DEFS} -DWITH_SDL)
    set(INCLUDE_DIRS ${INCLUDE_DIRS} ${SDL_INCLUDE_DIR})
    set(KONGOMATO_LINK_LIBS ${KONGOMATO_LINK_LIBS} ${SDL_LIBRARY})
    if(SDLIMAGE_FOUND)
    	set(INCLUDE_DIRS ${INCLUDE_DIRS} ${SDL_IMAGE_INCLUDE_DIR})
	set(KONGOMATO_LINK_LIBS ${KONGOMATO_LINK_LIBS} ${SDLIMAGE_LIBRARY})
    endif()
endif()


add_definitions(${GLOBAL_DEFS})
include_directories(${INCLUDE_DIRS})
link_directories(${LINK_DIRS})
add_library (kongomato SHARED ${KONGOMATO_CPPS})
set_target_properties(kongomato PROPERTIES COMPILE_DEFINITIONS BUILD_DLL)
target_link_libraries (kongomato ${KONGOMATO_LINK_LIBS})

if(${BUILD_TEST})
    add_executable(test ${TEST_CPPS})
    target_link_libraries(test ${TEST_LINK_LIBS})
endif()

if(${BUILD_TEST2D})
    add_executable(test2d ${TEST2D_CPPS})
    target_link_libraries(test2d ${TEST2D_LINK_LIBS})
endif()


