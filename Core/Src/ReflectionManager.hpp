
	class Attribute;
	class MethodBase;
	class Descriptor;
	class ReflectionManager : public Singleton<ReflectionManager>{
	public:
		ReflectionManager();
		~ReflectionManager();

		template<typename Type>
		static Attribute* makeAttribute(const std::string& name,Type* offset, const Descriptor* containerType){
			Attribute* a = new Attribute(name,static_cast<Uint>((INT_PTR)offset),getDescriptor<Type>(),containerType);
			return a;
		}

		template<typename Type>
		static const Descriptor* getDescriptor(Type* dummy = 0){
			typedef typename ValueType<Type>::Result ValueType0;
			if(!dummy)
				return DescriptorRetriever<ValueType0>::getDescriptor();
			return DescriptorRetriever<ValueType0>::getDescriptor((ValueType0*)dummy);
		}

		typedef std::map<const std::string, const Descriptor*> Descriptors;
		static bool registerDescriptor(const Descriptor* descriptor);
		const Descriptors& getDescriptors() const { return descriptors; }
		static const Descriptor* getDescriptor(const std::string& name);

		/*
		template< typename ReturnType, typename OwnerType >
		static MethodBase* makeMethod(const std::string& name, ReturnType (OwnerType::*method)(void) const){
			MethodBase* m = new ConstAccessor0<ReturnType,OwnerType>(name,method);
			return m;
		}
		*/

		template< typename ReturnType, typename OwnerType >
		static MethodBase* makeMethod(const std::string& name, ReturnType (OwnerType::*method)(void) const){
			MethodBase* m = new Accessor0<ReturnType,OwnerType>(name,method);
			return m;
		}

		template< typename ParamType1, typename OwnerType >
		static MethodBase* makeMethod(const std::string& name, void (OwnerType::*method)(ParamType1&) const){
			MethodBase* m = new Accessor1<ParamType1,OwnerType>(name,method);
			return m;
		}

		template< typename ParamType1, typename ParamType2,typename OwnerType >
		static MethodBase* makeMethod(const std::string& name, void (OwnerType::*method)(ParamType1&,ParamType2&) const){
			MethodBase* m = new Accessor2<ParamType1,ParamType2,OwnerType>(name,method);
			return m;
		}

		template< typename ParamType1, typename ParamType2, typename ParamType3,typename OwnerType >
		static MethodBase* makeMethod(const std::string& name, void (OwnerType::*method)(ParamType1&,ParamType2&,ParamType3&) const){
			MethodBase* m = new Accessor3<ParamType1,ParamType2,ParamType3,OwnerType>(name,method);
			return m;
		}

		template< typename ParamType1, typename ParamType2, typename ParamType3,typename ParamType4,typename OwnerType >
		static MethodBase* makeMethod(const std::string& name, void (OwnerType::*method)(ParamType1&,ParamType2&,ParamType3&,ParamType4&) const){
			MethodBase* m = new Accessor4<ParamType1,ParamType2,ParamType3,ParamType4,OwnerType>(name,method);
			return m;
		}

		template< typename OwnerType >
		static MethodBase* makeMethod(const std::string& name, void (OwnerType::*method)(void)){
			MethodBase* m = new Mutator0<OwnerType>(name,method);
			return m;
		}

		template< typename ParamType1, typename OwnerType >
		static MethodBase* makeMethod(const std::string& name, void (OwnerType::*method)(ParamType1)){
			MethodBase* m = new Mutator1<ParamType1,OwnerType>(name,method);
			return m;
		}

		template< typename ParamType1,typename ParamType2, typename OwnerType >
		static MethodBase* makeMethod(const std::string& name, void (OwnerType::*method)(ParamType1,ParamType2)){
			MethodBase* m = new Mutator2<ParamType1,ParamType2,OwnerType>(name,method);
			return m;
		}

		template< typename ParamType1,typename ParamType2,typename ParamType3, typename OwnerType >
		static MethodBase* makeMethod(const std::string& name, void (OwnerType::*method)(ParamType1,ParamType2,ParamType3)){
			MethodBase* m = new Mutator3<ParamType1,ParamType2,ParamType3,OwnerType>(name,method);
			return m;
		}

		template< typename ParamType1,typename ParamType2,typename ParamType3,typename ParamType4, typename OwnerType >
		static MethodBase* makeMethod(const std::string& name, void (OwnerType::*method)(ParamType1,ParamType2,ParamType3,ParamType4)){
			MethodBase* m = new Mutator4<ParamType1,ParamType2,ParamType3,ParamType4,OwnerType>(name,method);
			return m;
		}
	protected:
		Descriptors descriptors;
	};

	template<typename Type1, typename Type2>
	Type1* safeCast(Type2* o){
		const Descriptor* d2 = ReflectionManager::getInstance()->getDescriptor<Type2>(o);
		if(d2 && d2->isKindOf<Type1>()){
			return reinterpret_cast<Type1*>(o);
		}
		return 0;
	}