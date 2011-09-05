	class Descriptor;
	class NoType{
	public:
		static const Descriptor* getClassDescriptor(){ return 0;}
		static const Descriptor* getDescriptor(void* o){return 0;}
		virtual const Descriptor* getDescriptor(){return 0;}
	};

	template<typename Type = NoType>
	struct GetParentHelper{
		typedef Type Result;
	};

namespace luabridge{
	//SEB carrefull here as shared_ptr could make our non scripted objects deleted ...
	template <typename T>
	void tdstack<T>::push (lua_State *L, T data){
		const Descriptor* d = ReflectionManager::getDescriptor<T>();
		// Allocate a new userdata and construct the pointer in-place there
		void *block = lua_newuserdata(L, sizeof(shared_ptr<T>));
		new(block) shared_ptr<T>(&data);

		// Set the userdata's metatable
		luaL_getmetatable(L, d->getName().c_str());
		lua_setmetatable(L, -2);
	}

	template <typename T>
	T tdstack<T>::get (lua_State *L, int index){
		const Descriptor* d = ReflectionManager::getDescriptor<T>();
		shared_ptr<T> p = *(shared_ptr<T> *)checkclass(L, index,  d->getName().c_str());
		return *(p.get());
	}

	//SEB carrefull here as shared_ptr could make our non scripted objects deleted ...
	template <typename T>
	void tdstack<T*>::push (lua_State *L, T* data){
		const Descriptor* d = ReflectionManager::getDescriptor<T>();
		// Allocate a new userdata and construct the pointer in-place there
		void *block = lua_newuserdata(L, sizeof(shared_ptr<T>));
		new(block) shared_ptr<T>(data);

		// Set the userdata's metatable
		luaL_getmetatable(L, d->getName().c_str());
		lua_setmetatable(L, -2);
	}

	/* Implement if needed
	template <typename T>
	void tdstack <const T *>::push (lua_State *L, const T *data){
	}

	template <typename T>
	void tdstack <T* const>::push (lua_State *L, T * const data){
	}

	template <typename T>
	void tdstack <const T* const>::push (lua_State *L, const T * const data){
	}

	template <typename T>
	void tdstack <T&>::push (lua_State *L, T &data){
	}

	template <typename T>
	void tdstack <const T&>::push (lua_State *L, const T &data){
	}*/
}

#define CONCATENATE(str,d)\
	if(!str.empty() && d != NoType::getClassDescriptor())str += ",";\
	if(d != NoType::getClassDescriptor())str += d->getName()


	template<typename T1 = NoType, typename T2 = NoType, typename T3 = NoType, typename T4 = NoType, typename T5 = NoType, typename T6 = NoType, typename T7 = NoType>
	struct TypeNameConcatenator{
	public:
		static std::string get(){
			std::string res;
			CONCATENATE(res,ReflectionManager::getDescriptor<ValueType<T1>::Result>());
			CONCATENATE(res,ReflectionManager::getDescriptor<ValueType<T2>::Result>());
			CONCATENATE(res,ReflectionManager::getDescriptor<ValueType<T3>::Result>());
			CONCATENATE(res,ReflectionManager::getDescriptor<ValueType<T4>::Result>());
			CONCATENATE(res,ReflectionManager::getDescriptor<ValueType<T5>::Result>());
			CONCATENATE(res,ReflectionManager::getDescriptor<ValueType<T6>::Result>());
			CONCATENATE(res,ReflectionManager::getDescriptor<ValueType<T7>::Result>());
			return res;
		}
	};

#define CLASS_SCRIPT(name,type,parentType)\
	const Descriptor* parentTypeDescriptor = ReflectionManager::getDescriptor<parentType>();\
	luabridge::class__<type>& scriptClass = parentTypeDescriptor ?\
		LuaScriptManager::module().subclass<type>(LuaScriptManager::formatTypeName(name).c_str(),parentTypeDescriptor->getName().c_str()) :\
		LuaScriptManager::module().class_<type>(LuaScriptManager::formatTypeName(name).c_str());\
	scriptClass.constructor<void (*)()>()


#define TEMPLATE_CLASS_SCRIPT(name,type,parentType,...)\
	const Descriptor* parentTypeDescriptor = ReflectionManager::getDescriptor<parentType>();\
	luabridge::class__<type<__VA_ARGS__> >& scriptClass = parentTypeDescriptor ?\
		LuaScriptManager::module().subclass<type<__VA_ARGS__>>(LuaScriptManager::formatTypeName(name).c_str(),parentTypeDescriptor->getName().c_str()) :\
		LuaScriptManager::module().class_<type<__VA_ARGS__>>(LuaScriptManager::formatTypeName(name).c_str());\
	scriptClass.constructor<void (*)()>()

	/*luabridge::class__<type>& scriptClass = LuaScriptManager::module().class_<type>(\
		name.c_str()).constructor<void (*)()>()*/
	
#define SIMPLE_CLASS(name,...)\
public:\
	typedef GetParentHelper<__VA_ARGS__>::Result ParentType;\
	typedef name SelfType;\
	typedef TypedDescriptor<name> DescriptorType;\
	static const Descriptor* getClassDescriptor();\
	static bool classRegistration;

#define CLASS(name,...)\
	SIMPLE_CLASS(name,__VA_ARGS__);\
public:\
	template<typename Type>Boolean isKindOf()const {return getDescriptor()->isKindOf<Type>();}\
	Boolean isKindOf(const Descriptor* d)const {return getDescriptor()->isKindOf(d);}\
	static name* allocate(){return reinterpret_cast<name*>(name::getClassDescriptor()->allocate());}\
	void deallocate(name* o){name::getClassDescriptor()->deallocate(o);}\
	virtual const Descriptor* getDescriptor() const{return ReflectionManager::getDescriptor<name>();}


#define CLASS_IMP(declaration)\
	bool declaration::classRegistration = ReflectionManager::registerDescriptor(declaration::getClassDescriptor());\
	const Descriptor* declaration::getClassDescriptor(){\
	static Descriptor* descriptor;\
	if(descriptor)\
	return descriptor;\
	descriptor = new DescriptorType(#declaration, sizeof(declaration),\
		ReflectionManager::getDescriptor<ParentType>(), new DescriptorExtension(),"");\
	declaration* fakeInstance = 0;\
	Attribute* currentAttribute = 0;\
	MethodBase* currentMethod = 0;\
	CLASS_SCRIPT(descriptor->getName(),declaration,ParentType)

#define TEMPLATE_CLASS(name,...)\
public:\
	typedef GetParentHelper<__VA_ARGS__>::Result ParentType;\
	typedef name SelfType;\
	typedef TypedDescriptor< name > DescriptorType;\
	template<typename Ret>Boolean isKindOf()const {\
		return getDescriptor()->isKindOf<Ret>();\
	}\
	Boolean isKindOf(const Descriptor* d)const {return getDescriptor()->isKindOf(d);}\
	static name* allocate(){\
		return reinterpret_cast< name* >(name::getClassDescriptor()->allocate());\
	}\
	static void deallocate(name* o){\
		name::getClassDescriptor()->deallocate(o);\
	}\
	virtual const Descriptor* getDescriptor() const{\
		return ReflectionManager::getDescriptor< name >();\
	}
	
#define TEMPLATE_CLASS_IMP(declaration,...)\
	static const Descriptor* getClassDescriptor(){\
		static Descriptor* descriptor;\
		if(descriptor)\
			return descriptor;\
		descriptor = new DescriptorType(#declaration, sizeof(declaration),\
		ReflectionManager::getDescriptor<ParentType>(), new DescriptorExtension(),TypeNameConcatenator<##__VA_ARGS__>::get());\
		ReflectionManager::registerDescriptor(descriptor);\
		declaration* fakeInstance = 0;\
		Attribute* currentAttribute = 0;\
		MethodBase* currentMethod = 0;\
		CLASS_SCRIPT(descriptor->getName(),declaration,ParentType)

#define CLASS_END\
		return descriptor;}

#define ATTRIBUTE_BASE(attributeName)\
	currentAttribute = ReflectionManager::makeAttribute(#attributeName,\
	&fakeInstance->attributeName,descriptor);\
	descriptor->registerAttibute(currentAttribute)

#define ATTRIBUTE(attributeName)\
	ATTRIBUTE_BASE(attributeName);\
	scriptClass.property_rw(#attributeName, &SelfType::attributeName)

#define ATTRIBUTE_GET(attributeName, accessor)\
	ATTRIBUTE_BASE(attributeName);\
	currentAttribute->extension->registerAccessor(#accessor,accessor)\
	scriptClass.property_rw(#attributeName, accessor);\
	scriptClass.method(MethodBase::formatName(#accessor).c_str(), accessor)

#define ATTRIBUTE_GETSET(attributeName, accessor, mutator)\
	ATTRIBUTE_BASE(attributeName);\
	currentAttribute->extension->registerAccessor(#accessor,accessor);\
	currentAttribute->extension->registerMutator(#mutator,mutator);\
	scriptClass.property_rw(#attributeName, accessor, mutator);\
	scriptClass.method(MethodBase::formatName(#accessor).c_str(), accessor);\
	scriptClass.method(MethodBase::formatName(#mutator).c_str(), mutator)

#define ATTRIBUTE_ADD_REMOVE(attributeName, insertor, removor)\
	ATTRIBUTE_BASE(attributeName);\
	currentAttribute->extension->registerInsertor(#insertor,insertor);\
	currentAttribute->extension->registerRemovor(#removor,removor);\
	scriptClass.property_ro(#attributeName, &SelfType::attributeName);\
	scriptClass.method(MethodBase::formatName(#insertor).c_str(), insertor);\
	scriptClass.method(MethodBase::formatName(#removor).c_str(), removor)

#define FUNCTION(func)\
	currentMethod = ReflectionManager::makeMethod(#func,func);\
	descriptor->registerMethod(currentMethod);\
	scriptClass.method(MethodBase::formatName(#func).c_str(), func)

#define CLASS_MEMORY_CATEGORY(category)\
	descriptor->extension->setMemoryCategory(category)
	
#define CLASS_CONCEPT(concept)\
	descriptor->setConcept(ReflectionManager::getDescriptor<concept>())

#define CLASS_MIGRATION(func)\
	descriptor->extension->registerMigration(#func,func)

#define CLASS_VALIDATE(func)\
	descriptor->extension->registerValidate(#func,func)

#define CLASS_SERIALIZE(func)\
	descriptor->extension->registerSerialize(#func,func)

#define CLASS_ATTRIBUTECHANGED(func)\
	descriptor->extension->registerAttributeChanged(#func,func)

#define ATTRIBUTE_EXTENSION_PARAM(param,value)\
	currentAttribute->extension->param = value

#define ATTRIBUTE_NOT_SERIALIZABLE\
	ATTRIBUTE_EXTENSION_PARAM(serializable,false);

#define DESCRIPTOR(type) ReflectionManager::getDescriptor<type>()
