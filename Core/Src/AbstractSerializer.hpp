
	class AbstractSerializer{
		CLASS(AbstractSerializer);
	public:
		AbstractSerializer();
		AbstractSerializer(Stream* _stream);

		Boolean isLoading() const { return stream && stream->getType() == Stream::eLoading; }

	//Native types serialization
		template<typename Type>
		void serialize(Type& v,const std::string& key = Stream::emptyKey) const{
			if(stream){
				stream->serialize(v,key);
			}
		}

	//Overrideable logic
	public:
		virtual void serializeAttributes(const AbstractObject& o) const;
		virtual AbstractObject serialize(const AbstractObject& o = AbstractObject()) const;

	protected:
		Stream* stream;
	};
