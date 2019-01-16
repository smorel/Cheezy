
class LuaScriptManager : public Singleton<LuaScriptManager>{
public:
	LuaScriptManager();
	virtual ~LuaScriptManager();

	static lua_State* globalState() { initialize(); return L; }
	static std::string formatTypeName(const std::string& str);

public:
	static void initialize();

protected:
	static lua_State *L;
	int errfunc_index;

	friend class LuaScript;
};