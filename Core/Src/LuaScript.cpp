
CLASS_IMP(LuaScript);
	ATTRIBUTE_GETSET(data,&LuaScript::getData,&LuaScript::setData);
	FUNCTION(&LuaScript::load);
	FUNCTION(&LuaScript::checkValidity);
	FUNCTION(&LuaScript::execute);
	FUNCTION(&LuaScript::pause);
	FUNCTION(&LuaScript::resume);
	FUNCTION(&LuaScript::kill);
CLASS_END;

void LuaScript::setData(const std::string& d){
	innerData().validityChecked = false;
	data = d;
}

const std::string& LuaScript::getData() const{
	return data;
}

void LuaScript::load(const std::string& path){
	data.clear();
	std::string line;
	std::ifstream myfile (path.c_str());
	if (myfile.is_open())
	{
		while ( myfile.good() )
		{
			getline (myfile,line);
			data.append( line );
			data.append("\r\n");
		}
		myfile.close();
	}
	else{
		//error could not open file
	}
}

void LuaScript::_newState(){
	if(innerData().refKeya > 0){
		luaL_unref(LuaScriptManager::getInstance()->L, LUA_REGISTRYINDEX, InnerData().refKeya);
	}
	innerData().L = lua_newthread(LuaScriptManager::getInstance()->L);
    innerData().refKeya = luaL_ref(LuaScriptManager::getInstance()->L, LUA_REGISTRYINDEX);
}

void LuaScript::checkValidity(){
	//if we pass the data as string !!!  luaL_loadstring( as, script.c_str() )
	if(data.empty())
		return;

	_newState();
    if (luaL_loadstring( innerData().L, data.c_str() )!= 0){
		// compile-time error
		innerData().lastCompileError = lua_tostring(innerData().L, -1);
		printf("%s\n",innerData().lastCompileError);
	}
}

void LuaScript::execute(){
	checkValidity();
    resume();
}

void LuaScript::pause(){
}

void LuaScript::resume(){
	if (lua_resume( innerData().L, 0 )!= 0){
		innerData().lastRuntimeError = lua_tostring(innerData().L, -1);
		printf("%s\n",innerData().lastRuntimeError);
	}
}

void LuaScript::kill(){
}