PROJECT(Application)


#3rd partys and additional include paths
SET(3rdParty_DIR ${Application_SOURCE_DIR}/../../3rdParty CACHE PATH "3rdParty Directory")
INCLUDE_DIRECTORIES(${3rdParty_DIR})
INCLUDE_DIRECTORIES(${Cheezy_SOURCE_DIR})
INCLUDE_DIRECTORIES(${CMAKE_BINARY_DIR}/Application/Src/)
INCLUDE_DIRECTORIES(../)


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

#Build and dependencies definition
ADD_LIBRARY(Application STATIC
	${ALL_CPP}
        ${ALL_H}
	${ALL_HPP}
	${ALL_CC}
	${Schematic_pch}
)

ADD_DEPENDENCIES(Application
	Serialization
	FlowChart
	)

TARGET_LINK_LIBRARIES( Application
	Serialization
	FlowChart
	)