
	CLASS_IMP(AbstractSerializer);
	CLASS_END;
	
	AbstractSerializer::AbstractSerializer()
		: stream(0){
	}

	AbstractSerializer::AbstractSerializer(Stream* _stream)
		: stream(_stream){
	}

	void AbstractSerializer::serializeAttributes(const AbstractObject& o) const{
	}

	AbstractObject AbstractSerializer::serialize(const AbstractObject& o) const{
		return AbstractObject();
	}
