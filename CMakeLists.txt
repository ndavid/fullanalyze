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



SET(ALL_SRC ${ALL_SRC}
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
    )


INCLUDE_DIRECTORIES(${SRC_DIR})

#####################################
### Search for needed packages
#####################################

#Find wxWidgets
FIND_PACKAGE( wxWidgets COMPONENTS base core gl aui REQUIRED )
IF( wxWidgets_FOUND )
	INCLUDE( ${wxWidgets_USE_FILE} )
ELSE()
	# For convenience. When we cannot continue, inform the user
	MESSAGE( FATAL_ERROR "wxWidgets not found ! Please set wxWidgets path ..." )
ENDIF()

#Pour utiliser le find xerces et xsd:
SET(CMAKE_MODULE_PATH "cmakeContrib")
FIND_PACKAGE(XercesC)
IF( XERCESC_FOUND )
	INCLUDE_DIRECTORIES( ${XERCESC_INCLUDE_DIR} )
ELSE()
	MESSAGE( FATAL_ERROR "XercesC not found ! Please set XercesC path ..." )
ENDIF()

FIND_PACKAGE(Xsd)
IF( XSD_FOUND )
	INCLUDE_DIRECTORIES( ${XSD_INCLUDE_DIR} )
	#MESSAGE("XSD Include Path : " ${XSD_INCLUDE_DIR} )
ELSE()
	MESSAGE( FATAL_ERROR "XSD not found ! Please set XSD path ..." )
ENDIF()


# Find BOOST
SET(Boost_ADDITIONAL_VERSIONS "1.37.0" "1.37" "1.38" "1.38.0" "1.39.0" "1.39")
FIND_PACKAGE( Boost 1.36 COMPONENTS filesystem system thread)
IF( Boost_FOUND )
    INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )
    #MESSAGE("Boost Include Path : " ${Boost_INCLUDE_DIR} )
ELSE()
	MESSAGE( FATAL_ERROR "Boost not found ! Please set Boost path ..." )
ENDIF()


#####################################
###                     Fin recherche des packages                         ###
#####################################

#######################
### Construction de l'executable ###
#######################

# Repertoire vers la libViewerITK pour construire les chemins d'include et de link
SET( GILVIEWER_PATH "../../GilViewer/trunk" CACHE PATH "GilViewer directory" )
LINK_DIRECTORIES( ${GILVIEWER_PATH}/lib )
INCLUDE_DIRECTORIES( ${GILVIEWER_PATH}/src )
INCLUDE_DIRECTORIES( ${GILVIEWER_PATH}/extern )


# Pour la lib de format :
SET( LIDAR_FORMAT_PATH "../../LidarFormat/trunk" CACHE PATH "LidarFormat directory" )
LINK_DIRECTORIES( ${LIDAR_FORMAT_PATH} )
INCLUDE_DIRECTORIES( ${LIDAR_FORMAT_PATH}/src )



SET(FullAnalyze_LIBRAIRIES GilViewer LidarFormat
						    ${wxWidgets_LIBRARIES}
						    ${Boost_LIBRARIES}
						    ${XERCESC_LIBRARIES}
						   )


IF(UNIX)

	ADD_DEFINITIONS(-Wall) 

	ADD_EXECUTABLE(FullAnalyze
						${ALL_SRC}
	               )

	TARGET_LINK_LIBRARIES( FullAnalyze 
								${FullAnalyze_LIBRAIRIES}
						 )


ENDIF(UNIX)
