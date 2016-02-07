
	CLASS_IMP(BinaryStream);
	CLASS_END;

	BinaryStream::BinaryStream(){

	}

	BinaryStream::BinaryStream(const std::string& filepath, EType _type)
		: Stream(_type){

		std::ios_base::open_mode m = (_type == eLoading) 
			? (std::ios_base::in) 
			: (std::ios_base::out | std::ios_base::trunc);
		m |= std::ios_base::binary;

		innerData().stream.open(filepath.c_str(),m);
		//S'assurer que le stream est bien ouvert create file si existe pas ...
	}

	BinaryStream::~BinaryStream(){
		innerData().stream.close();
	}
	
	Boolean BinaryStream::isValid() const{
		return innerData().stream.is_open();
	}

	void BinaryStream::serialize(Boolean& v,const std::string& key) const{
		serialize_internal(v);
	}

	void BinaryStream::serialize(Uint& v,const std::string& key) const{
		serialize_internal(v);
	}

	void BinaryStream::serialize(Integer& v,const std::string& key) const{
		serialize_internal(v);
	}

	void BinaryStream::serialize(Float& v,const std::string& key) const{
		serialize_internal(v);
	}

	void BinaryStream::serialize(Byte& v,const std::string& key) const{
		serialize_internal(v);
	}

	void BinaryStream::serialize(std::string& v,const std::string& key) const{
		//out.write(str, strlen(str))

		switch(type){
			case eLoading:	
				{
					Uint size = 0;
					innerData().stream.read(reinterpret_cast< char * >(&size), sizeof(size));
					std::vector< char > rawString(size);
					innerData().stream.read(&rawString[0], size);
					v = std::string(rawString.begin(), rawString.end());
					break;
				}
			case eSaving:
				{
					Uint size = v.size();
					innerData().stream.write(reinterpret_cast< char * >(&size), sizeof(size));
					innerData().stream << v;
					break;
				}
		}
	}
	
	void BinaryStream::beginSection(std::string& name) const{
		serialize(name,"");
	}

	void BinaryStream::endSection() const{
	}
	
	void BinaryStream::serializeSectionCount(Uint& count) const{
		serialize_internal(count);
	}