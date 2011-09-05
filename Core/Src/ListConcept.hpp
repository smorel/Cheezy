
	class ContainerConcept{
		CLASS(ContainerConcept);
	};

	class ContainerDescriptor : public Descriptor{
	public:
		ContainerDescriptor(const std::string& _name, const Uint _size, const Descriptor* _parentDescriptor,
			DescriptorExtension* ext,const std::string& subTypes)
			: Descriptor(_name,_size,_parentDescriptor,ext,subTypes){
				concept = ReflectionManager::getDescriptor<ContainerConcept>();
		}

		virtual const Descriptor* keyDescriptor(void* data) const = 0;
		virtual const Descriptor* valueDescriptor(void* data) const = 0;
		virtual Uint count(void* data) const = 0;
		virtual AbstractObject get(void* data,const AbstractObject& key) const = 0;
		virtual void insert(void* data,const AbstractObject& key, const AbstractObject& value) const = 0;
		virtual void remove(void* data,const AbstractObject& key) const = 0;
	};