
	DescriptorExtension::DescriptorExtension()
		: migrationMutator(0),validateMutator(0),serializeMutator(0),memoryCategory("Unknown"){
	}
	
	void DescriptorExtension::serialize(void* owner,const AbstractSerializer* s){
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

	
	void DescriptorExtension::migration(void* owner,const MigrationData* d){
		if(migrationMutator){
			std::vector<AbstractObject> args;
			args.push_back(std::move(AbstractObject(d)));
			migrationMutator->execute(owner,args);
		}
	}
