PROJECT(Application_Qt)

#Cmake version dependency checking
IF( ${CMAKE_MINOR_VERSION} GREATER 4 )
	CMAKE_POLICY(SET CMP0005 OLD)
ENDIF( ${CMAKE_MINOR_VERSION} GREATER 4 )

ADD_DEFINITIONS(-DQT_LARGEFILE_SUPPORT -DQT_DLL -DQT_GUI_LIB -DQT_UITOOLS_LIB
				-DQT_CORE_LIB -DQT_XML_LIB -DQT_THREAD_SUPPORT)
				
SET( QT_USE_QTOPENGL 1 )
SET( QT_USE_QTMAIN 1 )
SET( QT_USE_QTUITOOLS 1 )
SET( QT_USE_QTXML 1 )
FIND_PACKAGE( Qt4 REQUIRED )
INCLUDE(${QT_USE_FILE})

#3rd partys and additional include paths
SET(3rdParty_DIR ${Application_Qt_SOURCE_DIR}/../../3rdParty CACHE PATH "3rdParty Directory")
INCLUDE_DIRECTORIES(${3rdParty_DIR})
INCLUDE_DIRECTORIES(${Cheezy_SOURCE_DIR})
INCLUDE_DIRECTORIES(${CMAKE_BINARY_DIR}/Application_Qt/Src/)
INCLUDE_DIRECTORIES(../)

INCLUDE_DIRECTORIES(${CMAKE_BINARY_DIR}/CodeEditor_Qt/)
INCLUDE_DIRECTORIES(${Application_Qt_BINARY_DIR}/Src )


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

#Qt PReprocessor definitions
QT4_WRAP_UI( QT_UI_SRCS ${ALL_UI} )
QT4_ADD_RESOURCES(QT_RCC_SRCS ${ALL_QRC} )
QT4_WRAP_CPP( QT_MOC_SRCS ${ALL_H})

SET(ALL_GENERATED
      ${QT_UI_SRCS}
      ${QT_MOC_SRCS}
      ${QT_RCC_SRCS}
)
SOURCE_GROUP(QtGenerated FILES ${ALL_GENERATED})
set_source_files_properties(${QT_MOC_SRCS} PROPERTIES HEADER_FILE_ONLY true)

#Build and dependencies definition
ADD_LIBRARY(Application_Qt STATIC
	${ALL_CPP}
        ${ALL_H}
	${ALL_HPP}
	${ALL_CC}
	${QT_UI_SRCS} 
	${QT_MOC_SRCS} 
	${QT_RCC_SRCS} 
	${Application_Qt_pch}
)

ADD_DEPENDENCIES(Application_Qt
	Application
	CodeEditor_Qt
	)

TARGET_LINK_LIBRARIES( Application_Qt
	Application
	CodeEditor_Qt
	${QT_LIBRARIES}
	)