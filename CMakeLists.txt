cmake_minimum_required(VERSION 2.6.1)

PROJECT(Cheezy)

# Libraries and plugins
IF (EXISTS "${Cheezy_SOURCE_DIR}/Core")
	ADD_SUBDIRECTORY(Core)
ENDIF (EXISTS "${Cheezy_SOURCE_DIR}/Core")

IF (EXISTS "${Cheezy_SOURCE_DIR}/UnitTest")
	ADD_SUBDIRECTORY(UnitTest)
ENDIF (EXISTS "${Cheezy_SOURCE_DIR}/UnitTest")

IF (EXISTS "${Cheezy_SOURCE_DIR}/Runtime")
	ADD_SUBDIRECTORY(Runtime)
ENDIF (EXISTS "${Cheezy_SOURCE_DIR}/Runtime")

IF (EXISTS "${Cheezy_SOURCE_DIR}/Delegate")
	ADD_SUBDIRECTORY(Delegate)
ENDIF (EXISTS "${Cheezy_SOURCE_DIR}/Delegate")

IF (EXISTS "${Cheezy_SOURCE_DIR}/Implement")
	ADD_SUBDIRECTORY(Implement)
ENDIF (EXISTS "${Cheezy_SOURCE_DIR}/Implement")

IF (EXISTS "${Cheezy_SOURCE_DIR}/Serialization")
	ADD_SUBDIRECTORY(Serialization)
ENDIF (EXISTS "${Cheezy_SOURCE_DIR}/Serialization")

IF (EXISTS "${Cheezy_SOURCE_DIR}/Object")
	ADD_SUBDIRECTORY(Object)
ENDIF (EXISTS "${Cheezy_SOURCE_DIR}/Object")

IF (EXISTS "${Cheezy_SOURCE_DIR}/ObjectContext")
	ADD_SUBDIRECTORY(ObjectContext)
ENDIF (EXISTS "${Cheezy_SOURCE_DIR}/ObjectContext")

IF (EXISTS "${Cheezy_SOURCE_DIR}/AppTest")
	ADD_SUBDIRECTORY(AppTest)
ENDIF (EXISTS "${Cheezy_SOURCE_DIR}/AppTest")

IF (EXISTS "${Cheezy_SOURCE_DIR}/lua")
	ADD_SUBDIRECTORY(lua)
ENDIF (EXISTS "${Cheezy_SOURCE_DIR}/lua")

IF (EXISTS "${Cheezy_SOURCE_DIR}/Qt/CodeEditor_Qt")
	ADD_SUBDIRECTORY(Qt/CodeEditor_Qt)
ENDIF (EXISTS "${Cheezy_SOURCE_DIR}/Qt/CodeEditor_Qt")

IF (EXISTS "${Cheezy_SOURCE_DIR}/Application")
	ADD_SUBDIRECTORY(Application)
ENDIF (EXISTS "${Cheezy_SOURCE_DIR}/Application")

IF (EXISTS "${Cheezy_SOURCE_DIR}/Qt/Application_Qt")
	ADD_SUBDIRECTORY(Qt/Application_Qt)
ENDIF (EXISTS "${Cheezy_SOURCE_DIR}/Qt/Application_Qt")

IF (EXISTS "${Cheezy_SOURCE_DIR}/FlowChart")
	ADD_SUBDIRECTORY(FlowChart)
ENDIF (EXISTS "${Cheezy_SOURCE_DIR}/FlowChart")
