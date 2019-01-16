PROJECT(AppTest)
 
IF( ${CMAKE_MINOR_VERSION} GREATER 5 )
    CMAKE_POLICY(SET CMP0020 NEW)
ENDIF( ${CMAKE_MINOR_VERSION} GREATER 5 )

ADD_DEFINITIONS(-DQT_LARGEFILE_SUPPORT -DQT_DLL -DQT_GUI_LIB -DQT_UITOOLS_LIB
				-DQT_CORE_LIB -DQT_XML_LIB -DQT_THREAD_SUPPORT)
				
SET( QT_USE_QTOPENGL 1 )
SET( QT_USE_QTMAIN 1 )
SET( QT_USE_QTUITOOLS 1 )
SET( QT_USE_QTXML 1 )
find_package(Qt5Core CONFIG REQUIRED)
find_package(Qt5Widgets CONFIG REQUIRED)
find_package(Qt5Xml CONFIG REQUIRED)
find_package(Qt5PrintSupport CONFIG REQUIRED)
#INCLUDE(${QT_USE_FILE})

# Always include the PerformanceStudio base directory
INCLUDE_DIRECTORIES(${AppTest_SOURCE_DIR})
INCLUDE_DIRECTORIES(${AppTest_BINARY_DIR} )

SET(3rdParty_DIR ${AppTest_SOURCE_DIR}/../../3rdParty CACHE PATH "3rdParty Directory")
SET(AppTest_ASSETS_DIR ${AppTest_SOURCE_DIR}/Embedded_Resources CACHE PATH "Resources Directory")

# we need this to be able to include headers produced by uic in our code
# (CMAKE_BINARY_DIR holds a path to the build directory, 
# while INCLUDE_DIRECTORIES() works just like INCLUDEPATH from qmake)
INCLUDE_DIRECTORIES( ${CMAKE_BINARY_DIR} )

INCLUDE_DIRECTORIES(${3rdParty_DIR})
INCLUDE_DIRECTORIES(${CMAKE_BINARY_DIR}/AppTest/Src/)
INCLUDE_DIRECTORIES(${Cheezy_SOURCE_DIR}/)

SET(AppTest_SC_BRANCH "${AppTest_SOURCE_DIR}" CACHE STRING "AppTests Source Control Branch")
SET(AppTest_SC_VERSION 0 CACHE INT "AppTest Source Control Revision")
SET(AppTest_BUILD_LABEL "local_build" CACHE STRING "AppTest CI Server Build Label")

##########################################################################
# Put the libaries and binaries that get built into directories at the
# top of the build tree rather than in hard-to-find leaf
# directories. This simplifies manual testing and the use of the build
# tree rather than installed Core libraries.
IF(WIN32)
	SET(EXECUTABLE_FORMAT WIN32)

	SET(LIBRARY_OUTPUT_PATH ${Cheezy_SOURCE_DIR}/bin/AppTest/win32/)
	SET(EXECUTABLE_OUTPUT_PATH ${Cheezy_SOURCE_DIR}/bin/AppTest/win32/)
	LINK_DIRECTORIES(${Cheezy_SOURCE_DIR}/bin/$(PlatformName)/)

ENDIF(WIN32)

FILE(GLOB ALL_CPP "./Src/*.cpp")
SOURCE_GROUP(Src FILES ${ALL_CPP})
FILE(GLOB ALL_H "./Src/*.h")
SOURCE_GROUP(Src FILES ${ALL_H})
FILE(GLOB ALL_HPP "./Src/*.hpp")
SOURCE_GROUP(Src FILES ${ALL_HPP})
FILE(GLOB ALL_CC "./Src/*.cc")
SOURCE_GROUP(Src FILES ${ALL_CC})
FILE(GLOB ALL_UI "./Resources/*.ui")
SOURCE_GROUP(Resources FILES ${ALL_UI})
FILE(GLOB ALL_QRC "./Resources/*.qrc")
SOURCE_GROUP(Resources FILES ${ALL_QRC})

#Remove .cpp from build to only compile .cc source blobs
set_source_files_properties(${ALL_CPP} PROPERTIES HEADER_FILE_ONLY true)

QT5_WRAP_UI( QT_UI_SRCS ${ALL_UI} )
QT5_ADD_RESOURCES(QT_RCC_SRCS ${ALL_QRC} )
QT5_WRAP_CPP( QT_MOC_SRCS ${ALL_H})

SET(ALL_GENERATED
      ${QT_UI_SRCS}
      ${QT_MOC_SRCS}
      ${QT_RCC_SRCS}
)
SOURCE_GROUP(QtGenerated FILES ${ALL_GENERATED})
set_source_files_properties(${QT_MOC_SRCS} PROPERTIES HEADER_FILE_ONLY true)

#Build and dependencies definition
ADD_EXECUTABLE(AppTest ${EXECUTABLE_FORMAT}
        ${ALL_CPP}
        ${ALL_H}
	${ALL_HPP}
	${ALL_CC}
	${QT_UI_SRCS} 
	${QT_MOC_SRCS} 
	${QT_RCC_SRCS} 
	${AppTest_pch}
	)

ADD_DEPENDENCIES(AppTest
	Lua
	Core
	ObjectManagement
	Serialization
	FlowChart
	Application
	CodeEditor_Qt
	Application_Qt
	)

TARGET_LINK_LIBRARIES( AppTest
	Lua
	Core
	ObjectManagement
	Serialization
	FlowChart
	Application
	CodeEditor_Qt
	Application_Qt
	${QT_LIBRARIES}
	)
	
set(CMAKE_INCLUDE_CURRENT_DIR ON)
target_link_libraries(AppTest Qt5::Core)
target_link_libraries(AppTest Qt5::Widgets)
target_link_libraries(AppTest Qt5::Xml)

add_custom_command(
    TARGET AppTest POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:Qt5::Widgets>
        $<TARGET_FILE_DIR:AppTest>
)

add_custom_command(
    TARGET AppTest POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:Qt5::Core>
        $<TARGET_FILE_DIR:AppTest>
)

add_custom_command(
    TARGET AppTest POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:Qt5::Xml>
        $<TARGET_FILE_DIR:AppTest>
)


add_custom_command(
    TARGET AppTest POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:Qt5::PrintSupport>
        $<TARGET_FILE_DIR:AppTest>
)

add_custom_command(
    TARGET AppTest POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:Qt5::Gui>
        $<TARGET_FILE_DIR:AppTest>
)

###############################################################################
# Copy dlls needed by the core to the output directory
IF(WIN32)
	SET_TARGET_PROPERTIES( AppTest PROPERTIES LINK_FLAGS "/ENTRY:mainCRTStartup" )
ENDIF(WIN32)
