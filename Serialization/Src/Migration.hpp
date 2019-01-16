
	class Descriptor;
	class MigrationData{
		CLASS(MigrationData);
	};

	class MigrationAttributeLost : public MigrationData{
		CLASS(MigrationAttributeLost,MigrationData);
	public:
		MigrationAttributeLost(){}
		std::string attributeName;
		Variant value;
	};

	class MigrationAttributeTypeChange : public MigrationData{
		CLASS(MigrationAttributeTypeChange,MigrationData);
	public:
		MigrationAttributeTypeChange(){}
		const Attribute* attribute;
		Variant value;
	};

	class MigrationAttributeNotInData : public MigrationData{
		CLASS(MigrationAttributeNotInData,MigrationData);
	public:
		MigrationAttributeNotInData(){}
		const Attribute* attribute;
	};

	class DescriptorMigrationExtension : public DescriptorExtension::Extension {
	public:
		DescriptorMigrationExtension();

		template<typename OwnerType>
		void registerMigration(const std::string& name,void (OwnerType::*method)(const MigrationData*)){
			migrationMutator = new Setter1<const MigrationData*,OwnerType>(name,method);
		}

		virtual void migration(void* owner,const MigrationData* d);
		
	protected:
		SetterBase* migrationMutator;
	};

	
	#define CLASS_MIGRATION(func)\
		DescriptorMigrationExtension* migrationExt = descriptor->extension->GetOrCreateExtension<DescriptorMigrationExtension>();\
		migrationExt->registerMigration(#func,func)