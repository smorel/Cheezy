
	CLASS_IMP(MigrationData);
	CLASS_END;

	CLASS_IMP(MigrationAttributeLost);
	CLASS_END;

	CLASS_IMP(MigrationAttributeTypeChange);
	CLASS_END;
	
	CLASS_IMP(MigrationAttributeNotInData);
	CLASS_END;

	
	DescriptorMigrationExtension::DescriptorMigrationExtension(): migrationMutator(0) {

	}

	void DescriptorMigrationExtension::migration(void* owner,const MigrationData* d){
		if(migrationMutator){
			std::vector<AbstractObject> args;
			args.push_back(std::move(AbstractObject(d)));
			migrationMutator->execute(owner,args);
		}
	}