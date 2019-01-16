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


#include "FastDelegate.hpp"
#include "FastDelegateBind.hpp"
using namespace fastdelegate;

#include "SignalSlot.hpp"
#include "SignalSlotDescriptors.hpp"

void linkDelegate();