class EnumConcept{
	CLASS(EnumConcept);
};

class EnumDescriptor : public Descriptor{
public:
	EnumDescriptor(const std::string& _name, const Uint _size, const Descriptor* _parentDescriptor,
		DescriptorExtension* ext,const std::string& subTypes)
			: Descriptor(_name,_size,_parentDescriptor,ext,subTypes){
				concept = ReflectionManager::getDescriptor<EnumConcept>();
	}

	void setValues(const std::string& values);

	Uint value(const std::string& str) const;
	const std::string& id(Uint value) const;

	const std::map<std::string,Uint>& getIdToValueMap() const{return idToValue;}
	const std::map<Uint,std::string>& getValueToIdMap() const{return valueToId;}

protected:

	std::map<std::string,Uint> idToValue;
	std::map<Uint,std::string> valueToId;
};

#define ENUM(name,...)\
	enum name{##__VA_ARGS__};\
	class name##Helper{\
	public:\
		name##Helper(){\
			str = #__VA_ARGS__;\
		}\
		static std::string str;\
	}

#define ENUM_IMP(name)\
	template<>\
	class DescriptorRetriever<name>{\
	public:\
		static const Descriptor* getDescriptor(){\
			_buildDescriptor();\
			return descriptor;\
		}\
		static const Descriptor* getDescriptor(name* o){\
			_buildDescriptor();\
			return descriptor;\
		}\
		static void serialize(void* data,const AbstractSerializer* s){\
			const EnumDescriptor* d = static_cast<const EnumDescriptor*>(ReflectionManager::getDescriptor<name>());\
			name& v = *(reinterpret_cast<name*>(data));\
			std::string strValue = s->isLoading() ? "" : d->id((Uint)v);\
			s->serialize(strValue);\
			if(s->isLoading()){\
				v = (name)d->value(strValue);\
			}\
		}\
	protected:\
		static void _buildDescriptor(){\
			if(!descriptor){\
				DescriptorExtension* ext = new DescriptorExtension();\
				descriptor = \
					new TypedDescriptor<name,EnumDescriptor>(#name,sizeof(name),0,ext,"");\
				ext->registerSerialize("serialize",&DescriptorRetriever<name>::serialize);\
				EnumDescriptor* ed = static_cast<EnumDescriptor*>(descriptor);\
				ed->setValues(name##Helper().str);\
				ReflectionManager::getInstance()->registerDescriptor(descriptor);\
			}\
		}\
		static Descriptor* descriptor;\
	};\
	Descriptor* DescriptorRetriever<name>::descriptor = 0;\
	std::string name##Helper::str;\
	template<>\
	class ParameterType<name>{\
	public:\
		typedef name Result;\
	};\
	template<>\
	class ReturnType<name>{\
	public:\
		typedef name Result;\
	};\
	template<> void fromString<name>(const std::string& str,name& res){\
		const EnumDescriptor* d = static_cast<const EnumDescriptor*>(ReflectionManager::getDescriptor<name>());\
		res = (name)d->value(str);\
	}\
	template<> void toString<name>(const name& v,std::string& str){\
		const EnumDescriptor* d = static_cast<const EnumDescriptor*>(ReflectionManager::getDescriptor<name>());\
		str = d->id((Uint)v);\
	}
