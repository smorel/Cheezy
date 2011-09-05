CLASS_IMP(EnumConcept);
CLASS_END;

Uint EnumDescriptor::value(const std::string& str) const{
	std::map<std::string,Uint>::const_iterator itFound = 
		idToValue.find(str);
	if(itFound != idToValue.end()){
		return itFound->second;
	}

	static Uint defaultValue = 0;
	return defaultValue;
}

const std::string& EnumDescriptor::id(Uint value) const{
	std::map<Uint,std::string>::const_iterator itFound = 
		valueToId.find(value);
	if(itFound != valueToId.end()){
		return itFound->second;
	}

	static std::string defaultValue;
	return defaultValue;
}

void EnumDescriptor::setValues(const std::string& values){
	idToValue.clear();
	valueToId.clear();

	typedef std::vector<std::string> StringList;
	StringList items;
	str::split(values,",",items,false,false);
	for(StringList::size_type i=0;i < items.size(); ++i){
		std::string id;
		Uint value;

		std::string sItem = items[i];
		StringList nameValue;
		str::split(sItem,"=",nameValue,false,false);
		if(nameValue.size() == 1){//No Value !
			id = str::trim(nameValue[0]);
			value = (Uint)i;
		}
		else if(nameValue.size() == 2){//has Value
			id = str::trim(nameValue[0]);
			std::string strvalue = str::trim(nameValue[1]);
			StringList valueOperation;
			str::split(strvalue,"<<",valueOperation,false,false);
			if(valueOperation.size() == 1){//Direct Value
				std::string strv = str::trim(valueOperation[0]);
				fromString<Uint>(strv,value);
			}
			else if(valueOperation.size() == 2){//Operation Value
				std::string strv1 = str::trim(valueOperation[0]);
				std::string strv2 = str::trim(valueOperation[1]);
				
				Uint v1 =0, v2 = 0;
				fromString<Uint>(strv1,v1);
				fromString<Uint>(strv2,v2);
				value = v1 << v2;
			}
			else{
				//ASSERT false : should not happend !
			}
		}
		else{
			//ASSERT false : should not happend !
		}

		if(!id.empty()){
			idToValue[id] = value;
			valueToId[value] = id;
		}
	}
}

namespace Enum_cpp{
	struct toto{
		ENUM(ETest,
			eTest1 = 1,
			eTest2 = 2,
			eTest12 = 12
			);
	};
};

ENUM_IMP(Enum_cpp::toto::ETest);

MAKE_TEST(EnumTest){
	const EnumDescriptor* d = static_cast<const EnumDescriptor*>(ReflectionManager::getDescriptor<Enum_cpp::toto::ETest>());

	const std::map<std::string,Uint>& idToValue = d->getIdToValueMap();
	for(std::map<std::string,Uint>::const_iterator it = idToValue.begin(); it != idToValue.end(); ++it){
		std::string id = it->first;
		Uint value = it->second;
		Uint vFromDesc = d->value(id);
		std::string sFromDesc = d->id(value);
		//ASSERT name.compare(sFromDesc) == 0;
		//ASSERT value == vFromDesc;
	}

	Enum_cpp::toto::ETest e = Enum_cpp::toto::eTest12;
	std::string s;
	toString(e,s);
	Enum_cpp::toto::ETest v;
	fromString(s,v);
	//ASSERT s.compare("eTest12") == 0 && e == v == 12;
};