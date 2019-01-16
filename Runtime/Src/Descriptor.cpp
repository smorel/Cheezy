
	Descriptor::Descriptor(const std::string& _name, const Uint _size, 
		const Descriptor* _parentDescriptor,DescriptorExtension* ext, 
		const std::string& subTypes)
		: name(_name),size(_size),parentDescriptor(_parentDescriptor),extension(ext),concept(0){
			ext->attachedDescriptor = this;
			if(!subTypes.empty()){
				name += "<";
				name += subTypes;
				name += ">";
			}
	}

	Descriptor::~Descriptor(){
		delete extension;
		extension = 0;
	}

	void Descriptor::registerAttibute(const Attribute* attribute){
		if(!attribute){
			//TODO : LOG
			return;
		}

		const std::string& name = attribute->getName();
		Attributes::const_iterator itFound = attributes.find(name);
		if(itFound != attributes.end()){
			//TODO : LOG
			return;
		}

		attributes[name] = attribute;
		orderedAttributes.push_back(attribute);
	}

	const Attribute* Descriptor::getAttribute(const std::string& attributeName) const {
		Attributes::const_iterator itFound = attributes.find(attributeName);
		if(itFound != attributes.end())
			return itFound->second;
		return parentDescriptor ? parentDescriptor->getAttribute(attributeName) : 0;
	}

	void Descriptor::registerMethod(const MethodBase* m){
		if(!m){
			//TODO : LOG
			return;
		}

		const std::string& name = m->getName();
		Methods::const_iterator itFound = methods.find(name);
		if(itFound != methods.end()){
			//TODO : LOG
			return;
		}

		methods[name] = m;
		orderedMethods.push_back(m);
	}

	const MethodBase* Descriptor::getMethod(const std::string& name) const{
		Methods::const_iterator itFound = methods.find(name);
		if(itFound != methods.end())
			return itFound->second;
		return parentDescriptor ? parentDescriptor->getMethod(name) : 0;
	}

	
	Boolean Descriptor::isKindOf(const Descriptor* d) const{
		const Descriptor* p = this;
		while(p && p != d){
			p = p->parentDescriptor;
		}
		return (p != 0);
	}
		
	void* Descriptor::allocate() const{
		return MemoryManager::getInstance()->allocate(size,extension->getMemoryCategory());
	}

	void Descriptor::deallocate(void* memory) const{
		MemoryManager::getInstance()->deallocate(memory,extension->getMemoryCategory());
	}

	void Descriptor::copy(void* source, void* target) const{
		std::memcpy( target, source, size /* + 1 ???*/ );
	}
