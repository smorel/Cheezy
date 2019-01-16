
	CLASS_IMP(ISerializer);
	CLASS_END;
	
	ISerializer::ISerializer()
		: stream(0){
	}

	ISerializer::ISerializer(Stream* _stream)
		: stream(_stream){
	}

	void ISerializer::serializeAttributes(const AbstractObject& o) const{
	}

	AbstractObject ISerializer::serialize(const AbstractObject& o) const{
		return AbstractObject();
	}
