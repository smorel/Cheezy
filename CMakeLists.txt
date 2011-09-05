cmake_minimum_required(VERSION 2.6.1)

#cmake_policy(SET CMP0003 NEW)
#cmake_policy(SET CMP0005 NEW)

# This needs 2.6.1, else cmake will warn, but the build thinks it's an error...
#cmake_policy(SET CMP0008 NEW)

PROJECT(UIViews)

MACRO(DeployDependencies _targetName dependecies)

	SET(Processed "")

	FOREACH(dependency ${dependecies})

		#Test for optimized or debug
		#Strip out dups, since target dependencies are convulted...

		IF(${dependency} MATCHES "optimized")

		ELSE(${dependency} MATCHES "optimized")
			IF (${dependency} MATCHES "debug")

			ELSE(${dependency} MATCHES "debug")

				SET(Skip 0)
				FOREACH(iter ${Processed})
					IF(${iter} STREQUAL ${dependency})
						SET(Skip 1)
					ENDIF(${iter} STREQUAL ${dependency})
				ENDFOREACH(iter )

				IF(NOT ${Skip})
					IF(WIN32)
						ADD_CUSTOM_COMMAND( TARGET ${_targetName} POST_BUILD
							COMMAND ${3rdParty_DIR}/Shell/cp
								ARGS -u -f -R ${dependency} ${EXECUTABLE_OUTPUT_PATH}${CMAKE_CFG_INTDIR}/
						)
					ELSE(WIN32)
						ADD_CUSTOM_COMMAND( TARGET ${_targetName} POST_BUILD
							COMMAND cp
								ARGS -Rf ${dependency} ${EXECUTABLE_OUTPUT_PATH}${CMAKE_CFG_INTDIR}/${PROJECT_NAME}.app/Contents/MacOS/
						)
					ENDIF(WIN32)
					# And add to processed list
					SET (Processed ${Processed} ${dependency})
				ENDIF(NOT ${Skip})
			ENDIF(${dependency} MATCHES "debug")
		ENDIF(${dependency} MATCHES "optimized")
	ENDFOREACH(dependency)

ENDMACRO(DeployDependencies _targetName dependecies)

# Libraries and plugins
IF (EXISTS "${UIViews_SOURCE_DIR}/Core")
	ADD_SUBDIRECTORY(Core)
ENDIF (EXISTS "${UIViews_SOURCE_DIR}/Core")

IF (EXISTS "${UIViews_SOURCE_DIR}/ObjectManagement")
	ADD_SUBDIRECTORY(ObjectManagement)
ENDIF (EXISTS "${UIViews_SOURCE_DIR}/ObjectManagement")

IF (EXISTS "${UIViews_SOURCE_DIR}/Serialization")
	ADD_SUBDIRECTORY(Serialization)
ENDIF (EXISTS "${UIViews_SOURCE_DIR}/Serialization")

IF (EXISTS "${UIViews_SOURCE_DIR}/AppTest")
	ADD_SUBDIRECTORY(AppTest)
ENDIF (EXISTS "${UIViews_SOURCE_DIR}/AppTest")

IF (EXISTS "${UIViews_SOURCE_DIR}/lua")
	ADD_SUBDIRECTORY(lua)
ENDIF (EXISTS "${UIViews_SOURCE_DIR}/lua")

IF (EXISTS "${UIViews_SOURCE_DIR}/luaBridge")
	ADD_SUBDIRECTORY(luaBridge)
ENDIF (EXISTS "${UIViews_SOURCE_DIR}/luaBridge")

IF (EXISTS "${UIViews_SOURCE_DIR}/CodeEditor_Qt")
	ADD_SUBDIRECTORY(CodeEditor_Qt)
ENDIF (EXISTS "${UIViews_SOURCE_DIR}/CodeEditor_Qt")

IF (EXISTS "${UIViews_SOURCE_DIR}/Application")
	ADD_SUBDIRECTORY(Application)
ENDIF (EXISTS "${UIViews_SOURCE_DIR}/Application")

IF (EXISTS "${UIViews_SOURCE_DIR}/Application_Qt")
	ADD_SUBDIRECTORY(Application_Qt)
ENDIF (EXISTS "${UIViews_SOURCE_DIR}/Application_Qt")

IF (EXISTS "${UIViews_SOURCE_DIR}/FlowChart")
	ADD_SUBDIRECTORY(FlowChart)
ENDIF (EXISTS "${UIViews_SOURCE_DIR}/FlowChart")
