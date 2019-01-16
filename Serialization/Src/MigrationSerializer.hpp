
	class MigrationSerializer : public ISerializer{
		CLASS(MigrationSerializer,ISerializer);
	public:
		MigrationSerializer();
		MigrationSerializer(Stream* _stream);
		
	public:
		virtual void serializeAttributes(const AbstractObject& o) const;
		virtual AbstractObject serialize(const AbstractObject& o = AbstractObject()) const;

	protected:
		void getAttributes(const Descriptor* d,std::set<const Attribute*>& allAttributes) const;
	};
