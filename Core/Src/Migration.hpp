
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
