
	CLASS_IMP(Stream);
	CLASS_END;
	
	std::string Stream::emptyKey = "value";
	
	Stream::Stream()
		:type(eUnknown){
	}

	Stream::Stream(EType _type)
		:type(_type){
	}
