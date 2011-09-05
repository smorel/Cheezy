
	Attribute::Attribute(const std::string& _name,unsigned int _offset,
		const Descriptor* _descriptor,const Descriptor* _containerDescriptor)
		: name(_name),offset(_offset),descriptor(_descriptor),containerDescriptor(_containerDescriptor){
		extension = new AttributeExtension();
	}
	
	Attribute::~Attribute(){
		delete extension;
		extension = 0;
	}
	
	AbstractObject Attribute::get(void* owner) const{
		//if no accessor
		if(!extension->accessor){
			Byte* adress = (Byte*)owner + offset;
			return AbstractObject((void*)adress,descriptor);
		}
		else{
			//will probably not work
			std::vector<Variant> ret;
			extension->accessor->execute(owner, ret);
			return AbstractObject(ret[0].getAdress(),ret[0].getDescriptor());
		}
	}

	void Attribute::set(void* owner, AbstractObject o) const{
		if(!extension->mutator){
			Byte* adress = (Byte*)owner + offset;
			//ASSERT(o.getDescriptor() == descriptor);
			descriptor->copy(o.getAdress(),adress);
		}
		else{
			std::vector<AbstractObject> s;
			s.push_back(o);
			extension->mutator->execute(owner,s);
		}
	}

	
	void Attribute::add(void* owner,const AbstractObject& key, const AbstractObject& value) const{
		//Assert descriptor->isConcept<ContainerConcept>();
		if(!extension->insertor){
			const ContainerDescriptor* d = static_cast<const ContainerDescriptor*>(descriptor);
			d->insert(owner,key,value);
		}
		else{
			std::vector<AbstractObject> s;
			s.push_back(key);
			s.push_back(value);
			extension->insertor->execute(owner,s);
		}
	}

	void Attribute::remove(void* owner, const AbstractObject& key) const{
		//Assert descriptor->isConcept<ContainerConcept>();
		if(!extension->removor){
			const ContainerDescriptor* d = static_cast<const ContainerDescriptor*>(descriptor);
			d->remove(owner,key);
		}
		else{
			std::vector<AbstractObject> s;
			s.push_back(key);
			extension->removor->execute(owner,s);
		}
	}
