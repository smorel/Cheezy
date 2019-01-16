
	AbstractObject::AbstractObject()
		: adress(0),descriptor(0){
	}

	AbstractObject::AbstractObject(const AbstractObject& other){
		set(other.adress,other.descriptor);
	}

	void AbstractObject::set(void* _memory, const Descriptor* _descriptor){
			adress = _memory;
			descriptor = _descriptor;
	}

	
	Boolean AbstractObject::isValid() const{
		return adress && descriptor;
	}
