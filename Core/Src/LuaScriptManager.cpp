
lua_State* LuaScriptManager::L = nullptr;

LuaScriptManager::LuaScriptManager()
	: Singleton<LuaScriptManager>(){
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