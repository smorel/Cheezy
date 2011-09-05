
class LuaScriptManager : public Singleton<LuaScriptManager>{
public:
	LuaScriptManager();
	virtual ~LuaScriptManager();

	static luabridge::module& module();
	static std::string formatTypeName(const std::string& str);

protected:
	static void initialize();

protected:
	lua_State *L;
	int errfunc_index;
	luabridge::module *M;

	friend class LuaScript;
};