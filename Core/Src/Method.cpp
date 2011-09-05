
	MethodBase::MethodBase(const std::string& _name)
		: name(formatName(_name)),methodType(eUnknown){
		extension = new MethodExtension();
	}

	MethodBase::~MethodBase(){
		delete extension;
		extension = 0;
	}

	std::string MethodBase::formatName(const std::string& name){
		std::string res = name;
		size_t found = res.find_last_of("::");
		res = res.substr(found+1);
		return res;
	}
