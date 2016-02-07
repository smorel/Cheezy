cmake_minimum_required(VERSION 2.6.1)

PROJECT(Cheezy)

# Libraries and plugins
IF (EXISTS "${Cheezy_SOURCE_DIR}/Core")
	ADD_SUBDIRECTORY(Core)
ENDIF (EXISTS "${Cheezy_SOURCE_DIR}/Core")

IF (EXISTS "${Cheezy_SOURCE_DIR}/ObjectManagement")
	ADD_SUBDIRECTORY(ObjectManagement)
ENDIF (EXISTS "${Cheezy_SOURCE_DIR}/ObjectManagement")

IF (EXISTS "${Cheezy_SOURCE_DIR}/Serialization")
	ADD_SUBDIRECTORY(Serialization)
ENDIF (EXISTS "${Cheezy_SOURCE_DIR}/Serialization")

IF (EXISTS "${Cheezy_SOURCE_DIR}/AppTest")
	ADD_SUBDIRECTORY(AppTest)
ENDIF (EXISTS "${Cheezy_SOURCE_DIR}/AppTest")

IF (EXISTS "${Cheezy_SOURCE_DIR}/lua")
	ADD_SUBDIRECTORY(lua)
ENDIF (EXISTS "${Cheezy_SOURCE_DIR}/lua")

IF (EXISTS "${Cheezy_SOURCE_DIR}/luaBridge")
	ADD_SUBDIRECTORY(luaBridge)
ENDIF (EXISTS "${Cheezy_SOURCE_DIR}/luaBridge")

IF (EXISTS "${Cheezy_SOURCE_DIR}/CodeEditor_Qt")
	ADD_SUBDIRECTORY(CodeEditor_Qt)
ENDIF (EXISTS "${Cheezy_SOURCE_DIR}/CodeEditor_Qt")

IF (EXISTS "${Cheezy_SOURCE_DIR}/Application")
	ADD_SUBDIRECTORY(Application)
ENDIF (EXISTS "${Cheezy_SOURCE_DIR}/Application")

IF (EXISTS "${Cheezy_SOURCE_DIR}/Application_Qt")
	ADD_SUBDIRECTORY(Application_Qt)
ENDIF (EXISTS "${Cheezy_SOURCE_DIR}/Application_Qt")

IF (EXISTS "${Cheezy_SOURCE_DIR}/FlowChart")
	ADD_SUBDIRECTORY(FlowChart)
ENDIF (EXISTS "${Cheezy_SOURCE_DIR}/FlowChart")
