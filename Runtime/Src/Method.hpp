
	class Descriptor;
	class MethodExtension;

	template<typename Type>
	struct getter{
		static Type& result(const AbstractObject& o){return *(o.get<Type>());}
	};

	template<typename Type>
	struct getter<Type&>{
		static Type result(const AbstractObject& o){return *(o.get<Type>());}
	};

	template<typename Type>
	struct getter<Type*>{
		static Type* result(const AbstractObject& o){return (o.get<Type>());}
	};

	template<>
	struct getter<void*>{
		static void* result(const AbstractObject& o){return o.getAdress();}
	};

	class MethodBase{
	public:
		MethodBase(const std::string& _name);
		~MethodBase();

		enum EMethodType{
			eUnknown,
			eGetter,
			eSetter
		};

		enum EType{
			eInstance,
			eStatic
		};

		const std::string& getName() const { return name;}

		const std::vector<const Descriptor*>& getReturnTypes() const { return returnTypes; }
		const std::vector<const Descriptor*>& getAttributeTypes() const { return attributesType; }

		EMethodType getMethodType() const { return methodType; }
		EType getType() const { return type; }

	public:
		static std::string formatName(const std::string& name);
		const std::string name;

		std::vector<const Descriptor*> returnTypes;
		std::vector<const Descriptor*> attributesType;

	public:
		MethodExtension* extension;
		EMethodType methodType;
		EType type;
	};


	class GetterBase : public MethodBase{
	public:
		GetterBase(const std::string& _name)
			: MethodBase(_name){
				methodType = eGetter;
				type = eInstance;
		}

		virtual void execute(void* owner, std::vector<Variant>& retValues) const = 0;
	};

	template< typename Type0, typename OwnerType >
	class Getter0 : public GetterBase{
	public:
		typedef typename ValueType<Type0>::Result	ValueType0;
        typedef Type0 (OwnerType::*MethodType)(void) const;
		Getter0(const std::string& _name,MethodType m)
			: GetterBase(_name),m_pMethod(m){
			returnTypes.push_back(ReflectionManager::getDescriptor<ValueType0>());
		}

		virtual void execute(void* owner, std::vector<Variant>& retValues)const {
			OwnerType * pTypedOwner(reinterpret_cast< OwnerType * >(owner)); 
			Type0 rt = (Type0)(pTypedOwner->*m_pMethod)();
			retValues.push_back(Variant(rt));
		}

	private:
        MethodType m_pMethod;
	};

	template< typename ParamType1, typename OwnerType >
	class Getter1 : public GetterBase{
	public:
        typedef void (OwnerType::*MethodType)(ParamType1&) const;
		Getter1(const std::string& _name,MethodType m)
			: GetterBase(_name),m_pMethod(m){
			returnTypes.push_back(ReflectionManager::getDescriptor<ParamType1>());
		}

		virtual void execute(void* owner, std::vector<Variant>& retValues)const {
			OwnerType * pTypedOwner(reinterpret_cast< OwnerType * >(owner)); 
			ParamType1 p1;
			(pTypedOwner->*m_pMethod)(p1);
			retValues.push_back(Variant(p1));
		}

	private:
        MethodType m_pMethod;
	};

	template< typename ParamType1, typename ParamType2,typename OwnerType >
	class Getter2 : public GetterBase{
	public:
        typedef void (OwnerType::*MethodType)(ParamType1&,ParamType2&) const;
		Getter2(const std::string& _name,MethodType m)
			: GetterBase(_name),m_pMethod(m){
			returnTypes.push_back(ReflectionManager::getDescriptor<ParamType1>());
			returnTypes.push_back(ReflectionManager::getDescriptor<ParamType2>());
		}

		virtual void execute(void* owner, std::vector<Variant>& retValues)const {
			OwnerType * pTypedOwner(reinterpret_cast< OwnerType * >(owner)); 
			ParamType1 p1;
			ParamType2 p2;
			(pTypedOwner->*m_pMethod)(p1,p2);
			retValues.push_back(Variant(p1));
			retValues.push_back(Variant(p2));
		}

	private:
        MethodType m_pMethod;
	};

	template< typename ParamType1, typename ParamType2,typename ParamType3,typename OwnerType >
	class Getter3 : public GetterBase{
	public:
        typedef void (OwnerType::*MethodType)(ParamType1&,ParamType2&,ParamType3&) const;
		Getter3(const std::string& _name,MethodType m)
			: GetterBase(_name),m_pMethod(m){
			returnTypes.push_back(ReflectionManager::getDescriptor<ParamType1>());
			returnTypes.push_back(ReflectionManager::getDescriptor<ParamType2>());
			returnTypes.push_back(ReflectionManager::getDescriptor<ParamType3>());
		}

		virtual void execute(void* owner, std::vector<Variant>& retValues)const {
			OwnerType * pTypedOwner(reinterpret_cast< OwnerType * >(owner)); 
			ParamType1 p1;
			ParamType2 p2;
			ParamType3 p3;
			(pTypedOwner->*m_pMethod)(p1,p2,p3);
			retValues.push_back(Variant(p1));
			retValues.push_back(Variant(p2));
			retValues.push_back(Variant(p3));
		}

	private:
        MethodType m_pMethod;
	};

	template< typename ParamType1, typename ParamType2,typename ParamType3,typename ParamType4,typename OwnerType >
	class Getter4 : public GetterBase{
	public:
        typedef void (OwnerType::*MethodType)(ParamType1&,ParamType2&,ParamType3&,ParamType4&) const;
		Getter4(const std::string& _name,MethodType m)
			: GetterBase(_name),m_pMethod(m){
			returnTypes.push_back(ReflectionManager::getDescriptor<ParamType1>());
			returnTypes.push_back(ReflectionManager::getDescriptor<ParamType2>());
			returnTypes.push_back(ReflectionManager::getDescriptor<ParamType3>());
			returnTypes.push_back(ReflectionManager::getDescriptor<ParamType4>());
		}

		virtual void execute(void* owner, std::vector<Variant>& retValues)const {
			OwnerType * pTypedOwner(reinterpret_cast< OwnerType * >(owner)); 
			ParamType1 p1;
			ParamType2 p2;
			ParamType3 p3;
			ParamType4 p4;
			(pTypedOwner->*m_pMethod)(p1,p2,p3,p4);
			retValues.push_back(Variant(p1));
			retValues.push_back(Variant(p2));
			retValues.push_back(Variant(p3));
			retValues.push_back(Variant(p4));
		}

	private:
        MethodType m_pMethod;
	};

	class SetterBase : public MethodBase{
	public:
		SetterBase(const std::string& _name)
			: MethodBase(_name){
				methodType = eSetter;
				type = eInstance;
		}

		virtual void execute(void* owner, const std::vector<AbstractObject>& attributes)const  = 0; 
	};

	template< typename OwnerType >
	class Setter0 : public SetterBase{
	public:
        typedef void (OwnerType::*MethodType)(void);
		Setter0(const std::string& _name,MethodType m)
			: SetterBase(_name),m_pMethod(m){
		}

		virtual void execute(void* owner, const std::vector<AbstractObject>& attributes)const {
			OwnerType * pTypedOwner(reinterpret_cast< OwnerType * >(owner)); 
			(pTypedOwner->*m_pMethod)();
		}

	private:
        MethodType m_pMethod;
	};

	template< typename ParamType1, typename OwnerType >
	class Setter1 : public SetterBase{
	public:
        typedef void (OwnerType::*MethodType)(ParamType1);
		typedef typename ValueType<ParamType1>::Result	ValueType1;
		Setter1(const std::string& _name,MethodType m)
			: SetterBase(_name),m_pMethod(m){
			attributesType.push_back(ReflectionManager::getDescriptor<ValueType1>());
		}

		virtual void execute(void* owner, const std::vector<AbstractObject>& attributes)const {
			OwnerType * pTypedOwner(reinterpret_cast< OwnerType * >(owner)); 
			(pTypedOwner->*m_pMethod)(getter<ParamType1>::result(attributes[0]));
		}

	private:
        MethodType m_pMethod;
	};

	template< typename ParamType1,typename ParamType2, typename OwnerType >
	class Setter2 : public SetterBase{
	public:
        typedef void (OwnerType::*MethodType)(ParamType1,ParamType2);
		typedef typename ValueType<ParamType1>::Result	ValueType1;
		typedef typename ValueType<ParamType2>::Result	ValueType2;
		Setter2(const std::string& _name,MethodType m)
			: SetterBase(_name),m_pMethod(m){
			attributesType.push_back(ReflectionManager::getDescriptor<ValueType1>());
			attributesType.push_back(ReflectionManager::getDescriptor<ValueType2>());
		}

		virtual void execute(void* owner, const std::vector<AbstractObject>& attributes)const {
			OwnerType * pTypedOwner(reinterpret_cast< OwnerType * >(owner)); 
			(pTypedOwner->*m_pMethod)(
				getter<ParamType1>::result(attributes[0]),
				getter<ParamType2>::result(attributes[1]));
		}

	private:
        MethodType m_pMethod;
	};

	template< typename ParamType1,typename ParamType2>
	class StaticSetter2 : public SetterBase{
	public:
        typedef void (*MethodType)(ParamType1,ParamType2);
		typedef typename ValueType<ParamType1>::Result	ValueType1;
		typedef typename ValueType<ParamType2>::Result	ValueType2;
		StaticSetter2(const std::string& _name,MethodType m)
			: SetterBase(_name),m_pMethod(m){
			type = eStatic;
			attributesType.push_back(ReflectionManager::getDescriptor<ValueType1>());
			attributesType.push_back(ReflectionManager::getDescriptor<ValueType2>());
		}

		virtual void execute(void* owner, const std::vector<AbstractObject>& attributes)const {
			(*m_pMethod)(
				getter<ParamType1>::result(attributes[0]),
				getter<ParamType2>::result(attributes[1]));
		}

	private:
        MethodType m_pMethod;
	};

	template< typename ParamType1,typename ParamType2,typename ParamType3, typename OwnerType >
	class Setter3 : public SetterBase{
	public:
        typedef void (OwnerType::*MethodType)(ParamType1,ParamType2,ParamType3);
		typedef typename ValueType<ParamType1>::Result	ValueType1;
		typedef typename ValueType<ParamType2>::Result	ValueType2;
		typedef typename ValueType<ParamType3>::Result	ValueType3;
		Setter3(const std::string& _name,MethodType m)
			: SetterBase(_name),m_pMethod(m){
			attributesType.push_back(ReflectionManager::getDescriptor<ValueType1>());
			attributesType.push_back(ReflectionManager::getDescriptor<ValueType2>());
			attributesType.push_back(ReflectionManager::getDescriptor<ValueType3>());
		}

		virtual void execute(void* owner, const std::vector<AbstractObject>& attributes)const {
			OwnerType * pTypedOwner(reinterpret_cast< OwnerType * >(owner)); 
			(pTypedOwner->*m_pMethod)(
				getter<ParamType1>::result(attributes[0]),
				getter<ParamType2>::result(attributes[1]),
				getter<ParamType3>::result(attributes[2]));
		}

	private:
        MethodType m_pMethod;
	};

	template< typename ParamType1,typename ParamType2,typename ParamType3, typename ParamType4,typename OwnerType >
	class Setter4 : public SetterBase{
	public:
        typedef void (OwnerType::*MethodType)(ParamType1,ParamType2,ParamType3,ParamType4);
		typedef typename ValueType<ParamType1>::Result	ValueType1;
		typedef typename ValueType<ParamType2>::Result	ValueType2;
		typedef typename ValueType<ParamType3>::Result	ValueType3;
		typedef typename ValueType<ParamType4>::Result	ValueType4;
		Setter4(const std::string& _name,MethodType m)
			: SetterBase(_name),m_pMethod(m){
			attributesType.push_back(ReflectionManager::getDescriptor<ValueType1>());
			attributesType.push_back(ReflectionManager::getDescriptor<ValueType2>());
			attributesType.push_back(ReflectionManager::getDescriptor<ValueType3>());
			attributesType.push_back(ReflectionManager::getDescriptor<ValueType4>());
		}

		virtual void execute(void* owner, const std::vector<AbstractObject>& attributes)const {
			OwnerType * pTypedOwner(reinterpret_cast< OwnerType * >(owner)); 
			(pTypedOwner->*m_pMethod)(
				getter<ParamType1>::result(attributes[0]),
				getter<ParamType2>::result(attributes[1]),
				getter<ParamType3>::result(attributes[2]),
				getter<ParamType4>::result(attributes[4]));
		}

	private:
        MethodType m_pMethod;
	};