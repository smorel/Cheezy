
class LuaScriptManager : public Singleton<LuaScriptManager>{
public:
	LuaScriptManager();
	virtual ~LuaScriptManager();

	static lua_State* globalState() { initialize(); return L; }
	static std::string formatTypeName(const std::string& str);

public:
	static void initialize();

	template<typename Type>
	void pushToScript(Type& data,const std::string& name) const{
		luabridge::Stack<Type>::push(LuaScriptManager::L,data);
	}

	//TODO: register on descriptor changes in reflection manager and update bindings

protected:
	void initBridge();
	void initBridge(const Descriptor* desc);

	static lua_State *L;
	int errfunc_index;

	friend class LuaScript;
};