
	class DescriptorExtension{
	public:
		DescriptorExtension();

		const std::string& getMemoryCategory() const { return memoryCategory;}
		void setMemoryCategory(const std::string& category){memoryCategory = category;}

		template<typename OwnerType>
		void registerMigration(const std::string& name,void (OwnerType::*method)(const MigrationData*)){
			migrationMutator = new Mutator1<const MigrationData*,OwnerType>(name,method);
		}

		template<typename OwnerType>
		void registerValidate(const std::string& name,void (OwnerType::*method)(void)){
			validateMutator = new Mutator0<OwnerType>(name,method);
		}

		template<typename OwnerType>
		void registerSerialize(const std::string& name,void (OwnerType::*method)(void* owner,const AbstractSerializer* s)){
			serializeMutator = new Mutator2<void*,const AbstractSerializer*,OwnerType>(name,method);
		}

		void registerSerialize(const std::string& name,void (*method)(void* owner,const AbstractSerializer* s)){
			serializeMutator = new StaticMutator2<void*,const AbstractSerializer*>(name,method);
		}

		template<typename OwnerType>
		void registerAttributeChanged(const std::string& name, void (OwnerType::*method)(void)){
			attributeChangedMutator = new Mutator0<OwnerType>(name,method);
		}

		virtual void serialize(void* owner,const AbstractSerializer* s);
		virtual void migration(void* owner,const MigrationData* d);

	protected:
		friend class Descriptor;
		const Descriptor* attachedDescriptor;

		std::string memoryCategory;
		MutatorBase* migrationMutator;
		MutatorBase* validateMutator;
		MutatorBase* serializeMutator;
		MutatorBase* attributeChangedMutator;
	};
