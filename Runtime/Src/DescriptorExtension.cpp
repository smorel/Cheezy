
	DescriptorExtension::DescriptorExtension()
		: validateMutator(0),memoryCategory("Unknown"){
	}
	
	DescriptorSerializationExtension::DescriptorSerializationExtension(): serializeMutator(0) {

	}

	
	void DescriptorSerializationExtension::serialize(void* owner,const ISerializer* s){
		if(serializeMutator){
			std::vector<AbstractObject> args;
			args.push_back(std::move(AbstractObject(owner)));
			args.push_back(std::move(AbstractObject(s)));
			serializeMutator->execute(owner,args);
		}
		else{
			s->serializeAttributes(AbstractObject(owner, attachedDescriptor));
		}
	}

	
