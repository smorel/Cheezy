CLASS_IMP(ID);
	CLASS_SERIALIZE(&ID::serialize);
CLASS_END;

ID::ID(){
}

ID::ID(const ID& other){
	guid = other.guid;
}

ID::ID(const std::string& str){
	fromString(str);
}

ID ID::create(){
	ID id;
	UuidCreate(&id.guid); 
	return id;
}

std::string ID::toString() const{
	unsigned char * str;
	UuidToStringA(&guid, &str);
	std::string ret((char*)str);
    RpcStringFreeA ( &str );
	return ret;
}

void ID::fromString(const std::string& str){
	UuidFromStringA((unsigned char *)str.c_str(),&guid);
}

void ID::serialize(void* data, const ISerializer* s){
	if(s->isLoading()){
		std::string res;
		s->serialize(res);
		fromString(res);
	}
	else{
		std::string res = toString();
		s->serialize(res);
	}
}

Boolean operator == (const ID& one,const ID& other){
	return (Boolean)(one.guid == other.guid);
}

const ID& ID::operator = (const ID& other){
	guid = other.guid;
	return *this;
}

Boolean operator != (const ID& one,const ID& other){
	return (Boolean)(one.guid != other.guid);
}

Boolean operator < (const ID& one,const ID& other){
	if(one.guid.Data1 < other.guid.Data1)
		return true;
	else if(one.guid.Data1 > other.guid.Data1)
		return false;
	else{
		if(one.guid.Data2 < other.guid.Data2)
			return true;
		else if(one.guid.Data2 > other.guid.Data2)
			return false;
		else{
			if(one.guid.Data3 < other.guid.Data3)
				return true;
			else if(one.guid.Data3 > other.guid.Data3)
				return false;
			else{
				for(int i=0;i<4;++i){
					if(one.guid.Data4[i] < other.guid.Data4[i])
						return true;
					else if(one.guid.Data4[i] > other.guid.Data4[i])
						return false;
				}
			}
		}
	}
	return false;
}
