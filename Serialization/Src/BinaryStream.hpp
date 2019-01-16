
	class BinaryStream : public Stream{
		CLASS(BinaryStream,Stream);

	public:
		BinaryStream();
		BinaryStream(const std::string& _filepath, EType _type);
		~BinaryStream();
		
		virtual Boolean isValid() const;
		
		virtual void beginSection(std::string& name) const;
		virtual void serializeSectionCount(Uint& count) const;
		virtual void endSection() const;

		virtual void serialize(Boolean& v,const std::string& key = Stream::emptyKey) const;
		virtual void serialize(Uint& v,const std::string& key = Stream::emptyKey) const;
		virtual void serialize(Integer& v,const std::string& key = Stream::emptyKey) const;
		virtual void serialize(Float& v,const std::string& key = Stream::emptyKey) const;
		virtual void serialize(Byte& v,const std::string& key = Stream::emptyKey) const;
		virtual void serialize(std::string& v,const std::string& key = Stream::emptyKey) const;

	protected:
		template<typename Type>
		void serialize_internal(Type& v) const{
			switch(type){
			case eLoading:
				//innerData().stream >> v;
				innerData().stream.read((char*)(&v),sizeof(Type));
				break;
			case eSaving:
				//innerData().stream << v;
				innerData().stream.write((char*)(&v),sizeof(Type));
				break;
			}
		}

	protected:
		struct InnerData{
			std::fstream stream;
		};
		mutable NoCopy<InnerData> innerData;
	};
