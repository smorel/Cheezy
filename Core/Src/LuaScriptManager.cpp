
LuaScriptManager::LuaScriptManager()
	: Singleton<LuaScriptManager>(),L(0),M(0){
}

LuaScriptManager::~LuaScriptManager(){
	if(L){
		lua_close(L);
	}

	if(M){
		delete M;
		M = 0;
	}
}

int traceback (lua_State *L){
	lua_getglobal(L, "debug");
	if (!lua_istable(L, -1))
	{
		lua_pop(L, 1);
		return 1;
	}
	lua_getfield(L, -1, "traceback");
	if (!lua_isfunction(L, -1))
	{
		lua_pop(L, 2);
		return 1;
	}
	lua_pushvalue(L, 1);  /* pass error message */
	lua_pushinteger(L, 2);  /* skip this function and traceback */
	lua_call(L, 2, 1);  /* call debug.traceback */
	return 1;
}

void LuaScriptManager::initialize(){
	if(!getInstance()->L && !getInstance()->M){
		getInstance()->L = luaL_newstate();

		// Provide the base libraries
		luaL_openlibs(getInstance()->L);

		getInstance()->M = new luabridge::module(getInstance()->L);

		// Put the traceback function on the stack
		lua_pushcfunction(getInstance()->L, &traceback);
		getInstance()->errfunc_index = lua_gettop(getInstance()->L);
	}
}

luabridge::module& LuaScriptManager::module(){
	initialize();
	return *(getInstance()->M);
}

std::string LuaScriptManager::formatTypeName(const std::string& str){
	//replace :: and < and , by _
	//relpace > by nothing
	return str::replace(str::replace(str::replace(str,"::","_"),"<","_"),">","");
}