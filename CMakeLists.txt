PROJECT( FullAnalyze )

cmake_minimum_required(VERSION 2.6)

# Useful for Eclipse code STL completion
if(UNIX)
	exec_program( gcc ARGS -dumpversion OUTPUT_VARIABLE GCC_VERSION )
	
	string( SUBSTRING ${GCC_VERSION} 0 3 GOOD_GCC_VERSION )
    include_directories( /usr/include/c++/${GOOD_GCC_VERSION} )
endif()


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

#Find wxWidgets
if ( WIN32 )
	FIND_PACKAGE(wxWidgets REQUIRED adv base gl core xml aui xrc html tiff jpeg png)
	IF(wxWidgets_FOUND)  
		INCLUDE(${wxWidgets_USE_FILE})
		include_directories( ${wxWidgets_ROOT_DIR}/src/jpeg )
		include_directories( ${wxWidgets_ROOT_DIR}/src/tiff )
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
SET(Boost_ADDITIONAL_VERSIONS "1.37.0" "1.37" "1.38" "1.38.0" "1.39.0" "1.39")
find_package( Boost 1.36 COMPONENTS filesystem system unit_test_framework)
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
	include_directories(${LidarFormat_INCLUDE_DIRS})
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

ADD_EXECUTABLE(FullAnalyze ${EXECUTABLE_WIN32}
					${ALL_SRC}
			   )

TARGET_LINK_LIBRARIES( FullAnalyze 
							${FullAnalyze_LIBRAIRIES} LidarFormat GilViewer
					 )
