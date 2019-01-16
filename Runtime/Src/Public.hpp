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

class ISerializer;
#include "MemoryManager.hpp"
#include "ReflectionMacros.hpp"
#include "Descriptor.hpp"
#include "ReflectionManager.hpp"
#include "AbstractObject.hpp"
#include "TypedDescriptor.hpp"
#include "Attribute.hpp"
#include "Variant.hpp"
#include "Method.hpp"
#include "DescriptorExtension.hpp"
#include "AttributeExtension.hpp"
#include "MethodExtension.hpp"
#include "ListConcept.hpp"
#include "Stream.hpp"
#include "ISerializer.hpp"
#include "NativeDescriptors.hpp"
#include "StlDescriptors.hpp"
#include "enum.hpp"

void linkRuntime();