
	class AttributeExtension{
	public:
		AttributeExtension();

		template<typename OwnerType,typename Type>
		void registerSetter(const std::string& name,void (OwnerType::*method)(Type v)){
			setter = new Setter1<Type,OwnerType>(name,method);
		}

		template<typename OwnerType,typename Type>
		void registerGetter(const std::string& name,Type (OwnerType::*method)() const){
			getter = new Getter0<Type,OwnerType>(name,method);
		}

		template<typename OwnerType,typename Type>
		void registerInserter(const std::string& name,void (OwnerType::*method)(Type v, Integer i)){
			inserter = new Setter2<Type,Integer,OwnerType>(name,method);
		}

		template<typename OwnerType,typename Type>
		void registerRemover(const std::string& name,Type (OwnerType::*method)(Integer i)){
			remover = new Setter1<Integer,OwnerType>(name,method);
		}

	public:
		Boolean serializable;
		
		GetterBase* getter;
		SetterBase* setter;
		
		SetterBase* inserter;
		SetterBase* remover;
	};
