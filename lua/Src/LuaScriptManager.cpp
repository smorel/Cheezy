
lua_State* LuaScriptManager::L = nullptr;

LuaScriptManager::LuaScriptManager()
	: Singleton<LuaScriptManager>(){
	initialize();
	initBridge();
}

LuaScriptManager::~LuaScriptManager(){
	if(L){
		lua_close(L);
	}
}

int traceback (lua_State *L){
	lua_getglobal (L, "debug");
	  if (!lua_istable (L, -1))
	  {
		lua_pop (L, 1);
		return 1;
	  }
	  lua_getfield (L, -1, "traceback");
	  if (!lua_isfunction (L, -1))
	  {
		lua_pop (L, 2);
		return 1;
	  }
	  lua_pushvalue (L, 1);  /* pass error message */
	  lua_pushinteger (L, 2);  /* skip this function and traceback */
	  lua_call (L, 2, 1);  /* call debug.traceback */
	return 1;
}

void LuaScriptManager::initialize(){
	if(!LuaScriptManager::L){
		//here should iterate over descriptors and create the lua bridge

		LuaScriptManager::L = nullptr;
		LuaScriptManager::L = luaL_newstate ();
		luaL_openlibs (LuaScriptManager::L);
		lua_pushcfunction (LuaScriptManager::L, &traceback);
		//getInstance()->errfunc_index = lua_gettop(LuaScriptManager::L);
	}
}

std::string LuaScriptManager::formatTypeName(const std::string& str){
	//replace :: and < and , by _
	//relpace > by nothing
	return str::replace(str::replace(str::replace(str,"::","_"),"<","_"),">","");
}


void LuaScriptManager::initBridge() {
	for (auto& pair : ReflectionManager::getInstance()->getDescriptors()) {
		initBridge(pair.second);
	}
}

void LuaScriptManager::initBridge(const Descriptor* desc) {
	const Descriptor* parentTypeDescriptor = desc->getParentDescriptor();
	
	//luabridge::Namespace::Class<type> scriptClass;

	//desc->registerForScripting<LuaScriptManager>(*this);
	/*
	if(parentTypeDescriptor == nullptr){ luabridge::getGlobalNamespace(LuaScriptManager::globalState()).beginClass <type> (scriptClass, name.c_str()); }
	else {luabridge::getGlobalNamespace(LuaScriptManager::globalState()).deriveClass <type,parentType> (scriptClass, name.c_str()); }
	scriptClass.addConstructor <void (*) ()> ()
	*/

	for (auto attribute : desc->getAttributes()) {
		/*scriptClass.addProperty(#attributeName, accessor, mutator);
		scriptClass.addFunction(MethodBase::formatName(#accessor).c_str(), accessor);
		scriptClass.addFunction(MethodBase::formatName(#mutator).c_str(), mutator)

		scriptClass.addData(#attributeName, &SelfType::attributeName);
		scriptClass.addFunction(MethodBase::formatName(#insertor).c_str(), insertor);
		scriptClass.addFunction(MethodBase::formatName(#removor).c_str(), removor)*/
	}
	
	for (auto method : desc->getMethods()) {
		//scriptClass.addFunction(MethodBase::formatName(#func).c_str(), func)
	}
}

/*
template<typename Type>
void LuaScriptManager::registerClass(const Descriptor* desc) {

}
	
template<typename Type, typename ParentType>
void LuaScriptManager::registerClass(const Descriptor* desc, const Descriptor* parentDesc) {

}

template<typename MemFn>
void LuaScriptManager::registerFunction(const Descriptor* desc, const MethodBase* method, MemFn function) {

}


implement own version of lua bridge   

template <class T>
  class Class : public ClassBase

  per Descriptor



    template <class FP>
    Class <T>& addStaticFunction (char const* name, FP const fp)
	
    template <class TG>
    Class <T>& addProperty (char const* name, TG (T::* get) () const)

    template <class TG, class TS>
    Class <T>& addProperty (char const* name, TG (T::* get) () const, void (T::* set) (TS))
	
    template <class TG, class TS = TG>
    Class <T>& addProperty (char const* name, TG (*get) (T const*), void (*set) (T*, TS) = 0)

    template <class U>
    Class <T>& addData (char const* name, const U T::* mp, bool isWritable = true)


*/
