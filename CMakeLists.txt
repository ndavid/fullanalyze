PROJECT( FullAnalyze )

cmake_minimum_required(VERSION 2.6)
set(FullAnalyze_version "000200")
# Useful for Eclipse code STL completion
if(UNIX)
	exec_program( gcc ARGS -dumpversion OUTPUT_VARIABLE GCC_VERSION )
	
	string( SUBSTRING ${GCC_VERSION} 0 3 GOOD_GCC_VERSION )
    include_directories( /usr/include/c++/${GOOD_GCC_VERSION} )
endif()
if(WIN32)
    if(MSVC)
		# Remove gil iterator related warnings...
        add_definitions(-D_CRT_SECURE_NO_DEPRECATE)
        add_definitions(-D_SCL_SECURE_NO_WARNINGS)
        #message( STATUS "MSVC_VERSION: " ${MSVC_VERSION} )
        #Visual C++, 32-bit, version 6.0         1200
        #Visual C++, 32-bit, version .net 2002   1300
        #Visual C++, 32-bit, version .net 2003   1310
        #Visual C++, 32-bit, version 2005        1400 (vc80)
        #Visual C++, 32-bit, version 2005 SP1    14?? (vc80_sp1)
        #Visual C++, 32-bit, version 2008        1500 (vc90)
		#MSVC90  (Visual C++ 2008 SP1) MSVC_VERSION=1500 (Compiler  Version 15.00.30729.01)
		#MSVC100 (Visual C++ 2010) MSVC_VERSION=1600 (Compiler  Version 16.00.30319.01)
        if(MSVC_VERSION EQUAL 1600)
			add_definitions( -D_HAS_CPP0X=0)
		endif()
    endif(MSVC)
endif(WIN32)

#Main src directory
SET(SRC_DIR ${CMAKE_SOURCE_DIR}/src)


#3d
AUX_SOURCE_DIRECTORY(${SRC_DIR}/3d SRC_3D)

#Core
AUX_SOURCE_DIRECTORY(${SRC_DIR}/core SRC_CORE)
AUX_SOURCE_DIRECTORY(${SRC_DIR}/core/algorithms/image SRC_CORE_ALGORITHMS_IMAGE)
AUX_SOURCE_DIRECTORY(${SRC_DIR}/core/algorithms/lidar SRC_CORE_ALGORITHMS_LIDAR)
AUX_SOURCE_DIRECTORY(${SRC_DIR}/core/modules SRC_CORE_MODULES)

#gui
AUX_SOURCE_DIRECTORY(${SRC_DIR}/gui SRC_GUI)
AUX_SOURCE_DIRECTORY(${SRC_DIR}/gui/3d SRC_GUI_3D)
AUX_SOURCE_DIRECTORY(${SRC_DIR}/gui/3d/wxFB SRC_GUI_3D_WXFB)
AUX_SOURCE_DIRECTORY(${SRC_DIR}/gui/files SRC_GUI_FILES)
AUX_SOURCE_DIRECTORY(${SRC_DIR}/gui/files/wxFB SRC_GUI_FILES_WXFB)
AUX_SOURCE_DIRECTORY(${SRC_DIR}/gui/images SRC_GUI_IMAGES)
AUX_SOURCE_DIRECTORY(${SRC_DIR}/gui/plot SRC_GUI_PLOT)


#tools
AUX_SOURCE_DIRECTORY(${SRC_DIR}/tools/files SRC_TOOLS)

#fullwave
OPTION(BUILD_FULLWAVE_SUPPORT "Build Fullwave support" OFF)
IF( BUILD_FULLWAVE_SUPPORT )
    AUX_SOURCE_DIRECTORY(${SRC_DIR}/3d/fullwave SRC_3D_FULLWAVE)
    AUX_SOURCE_DIRECTORY(${SRC_DIR}/core/modules/fullwave SRC_CORE_MODULES_FULLWAVE)
    AUX_SOURCE_DIRECTORY(${SRC_DIR}/gui/plot/fullwave SRC_GUI_PLOT_FULLWAVE)
    AUX_SOURCE_DIRECTORY(${SRC_DIR}/gui/3d/fullwave SRC_GUI_3D_FULLWAVE)
    AUX_SOURCE_DIRECTORY(${SRC_DIR}/gui/3d/fullwave/wxFB SRC_GUI_3D_FULLWAVE_WXFB)
    AUX_SOURCE_DIRECTORY(${SRC_DIR}/fullwave/algorithms SRC_FULLWAVE_ALGORITHMS)
    AUX_SOURCE_DIRECTORY(${SRC_DIR}/fullwave/format SRC_FULLWAVE_FORMAT)
    
    ADD_DEFINITIONS(-DBUILD_FULLWAVE)
ENDIF()

# Headers
file( GLOB ALL_HEADER_FILES ${SRC_DIR}/3d/*.h ${SRC_DIR}/3d/*.hpp
                            ${SRC_DIR}/core/*.h ${SRC_DIR}/core/*.hpp
                            ${SRC_DIR}/core/algorithms/image/*.h ${SRC_DIR}/core/algorithms/image/*.hpp
                            ${SRC_DIR}/core/algorithms/lidar/*.h ${SRC_DIR}/core/algorithms/lidar/*.hpp
                            ${SRC_DIR}/core/modules/*.h ${SRC_DIR}/core/modules/*.hpp
                            ${SRC_DIR}/core/gui/*.h ${SRC_DIR}/core/gui/*.hpp
                            ${SRC_DIR}/core/gui/3d/*.h ${SRC_DIR}/core/gui/3d/*.hpp
                            ${SRC_DIR}/core/gui/3d/wxFB/*.h ${SRC_DIR}/core/gui/3d/wxFB/*.hpp
                            ${SRC_DIR}/core/gui/files/*.h ${SRC_DIR}/core/gui/files/*.hpp
                            ${SRC_DIR}/core/gui/files/wxFB/*.h ${SRC_DIR}/core/gui/files/wxFB/*.hpp
                            ${SRC_DIR}/core/gui/images/*.h ${SRC_DIR}/core/gui/images/*.hpp
                            ${SRC_DIR}/core/gui/plot/*.h ${SRC_DIR}/core/gui/plot/*.hpp
                            ${SRC_DIR}/tools/files/*.h ${SRC_DIR}/tools/files/*.hpp
                            ${SRC_DIR}/3d/fullwave/*.h ${SRC_DIR}/3d/fullwave/*.hpp
                            ${SRC_DIR}/core/modules/fullwave/*.h ${SRC_DIR}/core/modules/fullwave/*.hpp
                            ${SRC_DIR}/gui/plot/fullwave/*.h ${SRC_DIR}/gui/plot/fullwave/*.hpp
                            ${SRC_DIR}/gui/3d/fullwave/*.h ${SRC_DIR}/gui/3d/fullwave/*.hpp
                            ${SRC_DIR}/gui/3d/fullwave/wxFB/*.h ${SRC_DIR}/gui/3d/fullwave/wxFB/*.hpp
                            ${SRC_DIR}/fullwave/algorithms/*.h ${SRC_DIR}/fullwave/algorithms/*.hpp
                            ${SRC_DIR}/fullwave/format/*.h ${SRC_DIR}/fullwave/format/*.hpp
)

#plugins
OPTION(BUILD_PLUGINS "Build plugins" OFF)
IF( BUILD_PLUGINS )
    include(${SRC_DIR}/plugins/CMakeLists.txt)
ENDIF()


SET(ALL_SRC
       ${SRC_3D}
       ${SRC_3D_FULLWAVE}
       ${SRC_CORE} 
       ${SRC_CORE_ALGORITHMS_IMAGE}
       ${SRC_CORE_ALGORITHMS_LIDAR}
       ${SRC_CORE_MODULES}
       ${SRC_CORE_MODULES_FULLWAVE}
       ${SRC_GUI}
       ${SRC_GUI_3D}
       ${SRC_GUI_3D_FULLWAVE}
       ${SRC_GUI_3D_FULLWAVE_WXFB}
       ${SRC_GUI_3D_WXFB}
       ${SRC_GUI_FILES}
       ${SRC_GUI_FILES_WXFB}
       ${SRC_GUI_IMAGES}
       ${SRC_GUI_PLOT}
       ${SRC_GUI_PLOT_FULLWAVE}
       ${SRC_TOOLS}
       ${SRC_FULLWAVE_ALGORITHMS}
       ${SRC_FULLWAVE_FORMAT}
       
       ${SRC_PLUGINS}
    )
   


INCLUDE_DIRECTORIES(${SRC_DIR})

#####################################
### Search for needed packages
#####################################
find_package(TIFF REQUIRED)
if(TIFF_FOUND)
	include_directories(${TIFF_INCLUDE_DIR})
else()
	message(FATAL_ERROR "TIFF not found ! Please set TIFF path ...")
endif()

find_package(JPEG REQUIRED)
if(JPEG_FOUND)
	include_directories(${JPEG_INCLUDE_DIR})
else()
	message(FATAL_ERROR "JPEG not found ! Please set JPEG path ...")
endif()

#Find wxWidgets
if ( WIN32 )
	FIND_PACKAGE(wxWidgets REQUIRED adv base gl core xml aui xrc html tiff jpeg png)
	IF(wxWidgets_FOUND)  
		INCLUDE(${wxWidgets_USE_FILE})
		include_directories( ${wxWidgets_ROOT_DIR}/src/png )
		include_directories( ${wxWidgets_ROOT_DIR}/src/zlib )
		
		SET(FullAnalyze_LIBRAIRIES ${FullAnalyze_LIBRAIRIES} ${wxWidgets_LIBRARIES})
	ELSE()
		MESSAGE(FATAL_ERROR "wxWidgets not found ! Please set wxWidgets path ...")
	ENDIF()
else()
	FIND_PACKAGE(wxWidgets REQUIRED adv base gl core xml aui xrc html )
	IF(wxWidgets_FOUND)  
		INCLUDE(${wxWidgets_USE_FILE})
		SET(FullAnalyze_LIBRAIRIES ${FullAnalyze_LIBRAIRIES} ${wxWidgets_LIBRARIES})
	ELSE()
		MESSAGE(FATAL_ERROR "wxWidgets not found ! Please set wxWidgets path ...")
	ENDIF()
endif()

# Find BOOST
# CMake does not include boost version 1.39
SET(BOOST_ROOT "" CACHE PATH " path to boost root directory")
SET(Boost_ADDITIONAL_VERSIONS 
          "1.37.0" "1.37" 
          "1.38" "1.38.0" 
          "1.39.0" "1.39"
           "1.40"
           "1.41"
          "1.42"
          "1.43"
          "1.44"
           "1.46" "1.46.1"
)
SET(Boost_USE_STATIC_LIBS OFF CACHE BOOL "use boost static lib")
SET(Boost_USE_MULTITHREADED ON CACHE BOOL "use boost multi thread lib")
SET(Boost_NO_SYSTEM_PATHS ON CACHE BOOL "don't use boost_root path variable")
find_package( Boost 1.36 COMPONENTS filesystem system)
if( Boost_FOUND )
	include_directories( ${Boost_INCLUDE_DIR} )
	link_directories( ${Boost_LIBRARY_DIRS} )
	# Autolink under Windows platforms
	if( NOT WIN32 )
		SET(FullAnalyze_LIBRAIRIES ${FullAnalyze_LIBRAIRIES} ${Boost_LIBRARIES})
	endif()
else()
	message( FATAL_ERROR "Boost not found ! Please set Boost path ..." )
endif()

FIND_PACKAGE(LidarFormat REQUIRED)
IF(LidarFormat_FOUND)
	MESSAGE(STATUS "LidarFormat_FOUND found !")
	include_directories(${LidarFormat_INCLUDE_DIRS} ) 
        MESSAGE(STATUS "LidarFormat_INCLUDE_DIRS "${LidarFormat_INCLUDE_DIRS}" ")
ELSE(LidarFormat_FOUND)
	# For convenience. inform the user
	MESSAGE(SEND_ERROR "LidarFormat not found ! check if you have still install this library
	and/or set the correct LidarFormatConfig path ")
ENDIF(LidarFormat_FOUND)

FIND_PACKAGE( GilViewer REQUIRED)
IF( GilViewer_FOUND)
	MESSAGE(STATUS " GilViewer_FOUND found !")
	include_directories(${GilViewer_INCLUDE_DIRS})
ELSE( GilViewer_FOUND)
	# For convenience. inform the user
	MESSAGE(SEND_ERROR " GilViewernot found ! check if you have still install this library
	and/or set the correct  GilViewerConfig path ")
ENDIF(GilViewer_FOUND)

# Option to choose to use GDAL/OGR
option(USE_GDAL_OGR "Build GilVeiwer with GDAL/OGR" OFF)
if(USE_GDAL_OGR)
    # Find GDAL
    find_package(GDAL)
    if(GDAL_FOUND)
        include_directories(${GDAL_INCLUDE_DIR})
    else()
        message(FATAL_ERROR "GDAL not found!")
    endif()
    set( GILVIEWER_USE_GDAL_OGR 1 )
else()
    set( GILVIEWER_USE_GDAL_OGR 0 )
endif()
#####################################
###                     Fin recherche des packages                         ###
#####################################

#######################
### Construction de l'executable ###
#######################

IF(UNIX)

	ADD_DEFINITIONS(-Wall) 
else()
	ADD_DEFINITIONS( -W3 )
	# Visual warnings on checked iterators
	ADD_DEFINITIONS( -D_SCL_SECURE_NO_WARNINGS )
	ADD_DEFINITIONS( -D_CRT_SECURE_NO_WARNINGS )
	
	SET(EXECUTABLE_WIN32 WIN32)
endif()

ADD_EXECUTABLE(FullAnalyze ${EXECUTABLE_WIN32} ${ALL_SRC} ${ALL_HEADER_FILES} )

TARGET_LINK_LIBRARIES( FullAnalyze ${FullAnalyze_LIBRAIRIES} LidarFormat GilViewer )
					 
INSTALL(TARGETS FullAnalyze DESTINATION bin)
