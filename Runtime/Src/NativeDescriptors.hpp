
	template<typename Type>
	class NativeDescriptor : public TypedDescriptor<Type>{
	public:
		NativeDescriptor(const std::string& _name, const Uint _size, const Descriptor* _parentDescriptor,
			DescriptorExtension* ext,const std::string& subTypes)
			: TypedDescriptor(_name,_size,_parentDescriptor,ext,subTypes){
		}

		//Implement specific native type code here (ex : serialization)
	};

	template<typename Type>
	class NativeDescriptorRegistrator{
	public:
		NativeDescriptorRegistrator(const std::string& name){
			if(!descriptor){
				DescriptorExtension* ext = new DescriptorExtension();
				
				DescriptorSerializationExtension* serializeExt = ext->GetOrCreateExtension<DescriptorSerializationExtension>();
				serializeExt->registerSerialize("serialize",&serialize);

				descriptor = new NativeDescriptor<Type>(name,sizeof(Type),0,ext,"");
				ReflectionManager::getInstance()->registerDescriptor(descriptor);
			}
		}

		static void serialize(void* data,const ISerializer* s){
			if(s->isLoading()){
				Type t;
				s->serialize<Type>(t);
				memcpy(data,&t,sizeof(Type));
			}
			else{
				Type t = *(reinterpret_cast<Type*>(data));
				s->serialize<Type>(t);
			}
		}

		static Descriptor* descriptor;
	};

	template<typename Type>
	Descriptor* NativeDescriptorRegistrator<Type>::descriptor = 0;

	template<>
	class DescriptorRetriever<void>{
	public:
		static const Descriptor* getDescriptor(){
			return 0;
		}

		static const Descriptor* getDescriptor(void* o){
			return 0;
		}
	};

	template<>
	class DescriptorRetriever<void*>{
	public:
		static const Descriptor* getDescriptor(){
			return 0;
		}

		static const Descriptor* getDescriptor(void* o){
			return 0;
		}
	};

	#define DECLARE_NATIVE_DESCRIPTOR(name)\
	static NativeDescriptorRegistrator<name> NativeDescriptorRegistrator_##name(#name);\
	template<>\
	class DescriptorRetriever<name>{\
	public:\
		static const Descriptor* getDescriptor(){\
			return NativeDescriptorRegistrator<name>::descriptor;\
		}\
		static const Descriptor* getDescriptor(name* o){\
			return NativeDescriptorRegistrator<name>::descriptor;\
		}\
	};\
	template<>\
	class ParameterType<name>{\
	public:\
		typedef name Result;\
	};\
	template<>\
	class ReturnType<name>{\
	public:\
		typedef name Result;\
	}

	
	DECLARE_NATIVE_DESCRIPTOR(Boolean);
	DECLARE_NATIVE_DESCRIPTOR(Uint);
	DECLARE_NATIVE_DESCRIPTOR(Integer);
	DECLARE_NATIVE_DESCRIPTOR(Float);
	DECLARE_NATIVE_DESCRIPTOR(Byte);

	
	template<>
	extern void fromString<Uint>(const std::string& str, Uint& res);
	template<>
	extern void toString<Uint>(const Uint& v,std::string& str);

	template<>
	extern void fromString<Integer>(const std::string& str, Integer& res);
	template<>
	extern void toString<Integer>(const Integer& v,std::string& str);
	
	template<>
	extern void fromString<Float>(const std::string& str, Float& res);
	template<>
	extern void toString<Float>(const Float& v,std::string& str);

	template<>
	extern void fromString<Byte>(const std::string& str, Byte& res);
	template<>
	extern void toString<Byte>(const Byte& v,std::string& str);

	template<>
	extern void fromString<Boolean>(const std::string& str, Boolean& res);
	template<>
	extern void toString<Boolean>(const Boolean& v,std::string& str);
	