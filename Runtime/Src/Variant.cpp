	CLASS_IMP(Variant);
		CLASS_SERIALIZE(&Variant::serialize);
	CLASS_END;

	void Variant::set(void* memory,const Descriptor* d){
		free();

		descriptor = d;
		if(d->getSize() > sizeof(void*)){
			adress = descriptor->allocate();
		}

		if(memory){
			if(d->getSize() > sizeof(void*))
				descriptor->copy(memory,adress);
			else{
				descriptor->copy(memory,&smallValue);
			}
		}
	}

	
	void Variant::free(){
		if(adress && descriptor){
			if(descriptor->getSize() > sizeof(void*))
				descriptor->deallocate(adress);
			adress = 0;
			smallValue = 0;
			descriptor = 0;
		}
	}

	void Variant::serialize(void* data, const ISerializer* s){
		DescriptorSerializationExtension* serializeExt = descriptor->extension->GetOrCreateExtension<DescriptorSerializationExtension>();
		if(s->isLoading()){
			std::string descName;
			s->serialize(descName);
			if(!descName.empty()){
				//allocate
				set(0,ReflectionManager::getDescriptor(descName));
				//ASSERT(descriptor)
				serializeExt->serialize(getAdress(),s);
			}
		}	
		else{
			s->serialize(descriptor ? descriptor->getName() : "");
			if(descriptor){
				serializeExt->serialize(getAdress(),s);
			}
		}
	}