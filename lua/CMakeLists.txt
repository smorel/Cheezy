PROJECT(Lua)

IF( ${CMAKE_MINOR_VERSION} GREATER 5 )
    CMAKE_POLICY(SET CMP0020 NEW)
ENDIF( ${CMAKE_MINOR_VERSION} GREATER 5 )

#3rd partys and additional include paths
SET(3rdParty_DIR ${Lua_SOURCE_DIR}/../../3rdParty CACHE PATH "3rdParty Directory")
INCLUDE_DIRECTORIES(${3rdParty_DIR})
INCLUDE_DIRECTORIES(${Cheezy_SOURCE_DIR})
INCLUDE_DIRECTORIES(${Cheezy_SOURCE_DIR}/lua/)
INCLUDE_DIRECTORIES(${Cheezy_SOURCE_DIR}/lua/Src/)
INCLUDE_DIRECTORIES(${Cheezy_SOURCE_DIR}/lua/3P/)
INCLUDE_DIRECTORIES(${Cheezy_SOURCE_DIR}/lua/3P/lua/)
INCLUDE_DIRECTORIES(${Cheezy_SOURCE_DIR}/lua/3P/luabridge/)
INCLUDE_DIRECTORIES(../)


FILE(GLOB ALL_C "./Src/*.cc")
SOURCE_GROUP(Src FILES ${ALL_C})
FILE(GLOB ALL_CPP  "./Src/*.cpp")
SOURCE_GROUP(Src FILES ${ALL_CPP})
FILE(GLOB ALL_H "./Src/*.h" "./Src/*.hpp")
SOURCE_GROUP(Src FILES ${ALL_H})

FILE(GLOB LUA_C "./3P/lua/*.c")
SOURCE_GROUP(Lua FILES ${LUA_C})
FILE(GLOB Lua_H  "./3P/lua/*.h" "./3P/luabridge/*.h")
SOURCE_GROUP(Lua FILES ${Lua_H})


#Remove .cpp from build to only compile .cc source blobs
set_source_files_properties(${ALL_CPP} PROPERTIES HEADER_FILE_ONLY true)

#Build and dependencies definition
ADD_LIBRARY(Lua STATIC
	${ALL_C}
	${ALL_CPP}
    ${ALL_H}
	${LUA_C}
    ${Lua_H}
)

ADD_DEPENDENCIES(Lua
	Core
    Runtime
    Object
	)
	
TARGET_LINK_LIBRARIES( Lua
	Rpcrt4
	Core
    Runtime
    Object
	)