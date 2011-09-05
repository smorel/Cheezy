#pragma once

#include <string>
#include <set>
#include <vector>
#include <list>
#include <map>
#include <iostream>
#include <fstream>

//for signal/slot
#include <windows.h>
//#include <pthread.h>

#include "assert.h"
#include "memory.h"
#include "sys\timeb.h"

// turn off MS Visual Studio warning: "Identifier was truncated to '255' characters in the debug information"
#pragma warning( disable : 4786 )
#pragma warning (disable:4996)

extern "C"
{
#include <Rpc.h>
#include <Lua/Src/lua.h>
#include <Lua/Src/lualib.h>
#include <Lua/Src/lauxlib.h>
#include <Lua/Src/lauxlib.h>
}

#include <LuaBridge/Src/luaBridge.hpp>

#include "FastDelegate.hpp"
#include "FastDelegateBind.hpp"
using namespace fastdelegate;

#include "Meta.hpp"
#include "NoCopy.hpp"
#include "NativeTypes.hpp"

#include "Singleton.hpp"
#include "MemoryManager.hpp"
#include "LuaScriptManager.hpp"
#include "ReflectionMacros.hpp"
#include "StringUtils.hpp"
#include "Descriptor.hpp"
#include "TypedDescriptor.hpp"
#include "AbstractObject.hpp"
#include "Variant.hpp"
#include "Attribute.hpp"
#include "Method.hpp"
#include "ReflectionManager.hpp"
#include "Migration.hpp"
#include "Stream.hpp"
#include "AbstractSerializer.hpp"
#include "NativeDescriptors.hpp"
#include "DescriptorExtension.hpp"
#include "AttributeExtension.hpp"
#include "MethodExtension.hpp"
#include "BinaryStream.hpp"
#include "ID.hpp"
#include "UnitTest.hpp"
#include "ListConcept.hpp"
#include "StlDescriptors.hpp"
#include "Object.hpp"
#include "LuaScript.hpp"
#include "enum.hpp"
#include "ImplementationFactory.hpp"
#include "SignalSlot.hpp"
#include "SignalSlotDescriptors.hpp"

void linkCore();