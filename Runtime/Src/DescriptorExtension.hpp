
	class DescriptorExtension{
	public:
		class Extension {
			friend class DescriptorExtension;
		public:
			Extension() : attachedDescriptor(0) {}
			virtual ~Extension() {}
		protected:
			const Descriptor* attachedDescriptor;
		};

		template<typename Type>
		Type* GetOrCreateExtension() {
			for (auto extension : extensions) {
				Type* casted = dynamic_cast<Type*>(extension);
				if(casted)
					return casted;
			}

			Type* extension = new Type();
			extension->attachedDescriptor = attachedDescriptor;
			extensions.push_back(extension);
			return extension;
		}

		DescriptorExtension();

		const std::string& getMemoryCategory() const { return memoryCategory;}
		void setMemoryCategory(const std::string& category){memoryCategory = category;}

		template<typename OwnerType>
		void registerValidate(const std::string& name,void (OwnerType::*method)(void)){
			validateMutator = new Setter0<OwnerType>(name,method);
		}

		template<typename OwnerType>
		void registerAttributeChanged(const std::string& name, void (OwnerType::*method)(void)){
			attributeChangedMutator = new Setter0<OwnerType>(name,method);
		}


	protected:
		friend class Descriptor;
		const Descriptor* attachedDescriptor;

		std::string memoryCategory;
		SetterBase* validateMutator;
		SetterBase* attributeChangedMutator;

		std::vector<Extension*> extensions;
	};

	
	class DescriptorSerializationExtension : public DescriptorExtension::Extension {
	public:
		DescriptorSerializationExtension();

		template<typename OwnerType>
		void registerSerialize(const std::string& name,void (OwnerType::*method)(void* owner,const ISerializer* s)){
			serializeMutator = new Setter2<void*,const ISerializer*,OwnerType>(name,method);
		}

		void registerSerialize(const std::string& name,void (*method)(void* owner,const ISerializer* s)){
			serializeMutator = new StaticSetter2<void*,const ISerializer*>(name,method);
		}
		
		virtual void serialize(void* owner,const ISerializer* s);
		
	protected:
		SetterBase* serializeMutator;
	};

	
#define CLASS_SERIALIZE(func)\
	DescriptorSerializationExtension* serializeExt = descriptor->extension->GetOrCreateExtension<DescriptorSerializationExtension>();\
	serializeExt->registerSerialize(#func,func)