
	class Stream{
		CLASS(Stream);

	public:
		enum EType{
			eUnknown,
			eLoading,
			eSaving};

		Stream();
		Stream(EType type);
		static std::string emptyKey;

		virtual Boolean isValid() const { return false; }

		virtual void beginSection(std::string& name) const{};
		virtual void serializeSectionCount(Uint& count) const{};
		virtual void endSection() const{};

		virtual void serialize(Boolean& v,const std::string& key = Stream::emptyKey) const {}
		virtual void serialize(Uint& v,const std::string& key = Stream::emptyKey) const {}
		virtual void serialize(Integer& v,const std::string& key = Stream::emptyKey) const {}
		virtual void serialize(Float& v,const std::string& key = Stream::emptyKey) const {}
		virtual void serialize(Byte& v,const std::string& key = Stream::emptyKey) const {}
		virtual void serialize(std::string& v,const std::string& key = Stream::emptyKey) const {}

		EType getType() const { return type; }
	protected:
		EType type;
	};
