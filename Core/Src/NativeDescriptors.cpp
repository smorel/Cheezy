	template<>
	void fromString<Uint>(const std::string& str, Uint& res){
		res = (Uint)atoi(str.c_str());
	}

	template<>
	void toString<Uint>(const Uint& v,std::string& str){
		char buffer[1028];
		sprintf_s(buffer,"%d",v);
		str = buffer;
	}

	template<>
	void fromString<Integer>(const std::string& str, Integer& res){
		res = (Integer)atoi(str.c_str());
	}

	template<>
	void toString<Integer>(const Integer& v,std::string& str){
		char buffer[1028];
		sprintf_s(buffer,"%d",v);
		str = buffer;
	}

	template<>
	void fromString<Float>(const std::string& str, Float& res){
		res = (Float)atof(str.c_str());
	}

	template<>
	void toString<Float>(const Float& v,std::string& str){
		char buffer[1028];
		sprintf_s(buffer,"%g",v);
		str = buffer;
	}

	template<>
	void fromString<Byte>(const std::string& str, Byte& res){
		//SEB TODO !!!!
		res = (Byte)atoi(str.c_str());
	}

	template<>
	void toString<Byte>(const Byte& v,std::string& str){
		char buffer[1028];
		//SEB TODO !!!!
		sprintf_s(buffer,"%d",v);
		str = buffer;
	}

	template<>
	void fromString<Boolean>(const std::string& str, Boolean& res){
		if(str.compare("true") == 0)
			res = true;
		else
			res = false;
	}

	template<>
	void toString<Boolean>(const Boolean& v,std::string& str){
		str = v ? "true" : "false";
	}
