PROJECT(LuaBridge)

#Cmake version dependency checking
IF( ${CMAKE_MINOR_VERSION} GREATER 4 )
	CMAKE_POLICY(SET CMP0005 OLD)
ENDIF( ${CMAKE_MINOR_VERSION} GREATER 4 )


#3rd partys and additional include paths
SET(3rdParty_DIR ${LuaBridge_SOURCE_DIR}/../../3rdParty CACHE PATH "3rdParty Directory")
INCLUDE_DIRECTORIES(${3rdParty_DIR})
INCLUDE_DIRECTORIES(${Cheezy_SOURCE_DIR})
INCLUDE_DIRECTORIES(${CMAKE_BINARY_DIR}/LuaBridge/Src/)
INCLUDE_DIRECTORIES(../)


FILE(GLOB ALL_CPP "./Src/*.cpp")
SOURCE_GROUP(Src FILES ${ALL_CPP})
FILE(GLOB ALL_HPP "./Src/*.hpp")
SOURCE_GROUP(Src FILES ${ALL_HPP})


#Build and dependencies definition
ADD_LIBRARY(LuaBridge STATIC
	${ALL_CPP}
        ${ALL_HPP}
)

ADD_DEPENDENCIES(LuaBridge
	Lua
	)

TARGET_LINK_LIBRARIES(LuaBridge
	Lua
	)