
	class AttributeExtension{
	public:
		AttributeExtension();

		template<typename OwnerType,typename Type>
		void registerMutator(const std::string& name,void (OwnerType::*method)(Type v)){
			mutator = new Mutator1<Type,OwnerType>(name,method);
		}

		template<typename OwnerType,typename Type>
		void registerAccessor(const std::string& name,Type (OwnerType::*method)() const){
			accessor = new Accessor0<Type,OwnerType>(name,method);
		}

		template<typename OwnerType,typename Type>
		void registerInsertor(const std::string& name,void (OwnerType::*method)(Type v, Integer i)){
			insertor = new Mutator2<Type,Integer,OwnerType>(name,method);
		}

		template<typename OwnerType,typename Type>
		void registerRemovor(const std::string& name,Type (OwnerType::*method)(Integer i)){
			removor = new Mutator1<Integer,OwnerType>(name,method);
		}

	public:
		Boolean serializable;
		
		AccessorBase* accessor;
		MutatorBase* mutator;
		
		MutatorBase* insertor;
		MutatorBase* removor;
	};
