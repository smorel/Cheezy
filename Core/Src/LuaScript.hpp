class LuaScript : public Object{
	CLASS(LuaScript,Object);
public:
	void load(const std::string& path);
	void checkValidity();
	void execute();
	void pause();
	void resume();
	void kill();

	/* check how to add/remove variables in lua script vie pair<string:name,Variant:value>
	   check how to instanciate luaScript and variables for run time execution
	   perhaps find a generic solution to the reusability problem of instances/configs/Edition ...
	*/

	void setData(const std::string& d);
	const std::string& getData() const;

protected:
	std::string data;

	class InnerData{
	public:
		InnerData() : L(0),refKeya(-1),validityChecked(false){
		}

		lua_State *L;
		int refKeya;
		bool validityChecked;

		std::string lastCompileError;
		std::string lastRuntimeError;
	};
	NoCopy<InnerData> innerData;

	void _newState();
};
