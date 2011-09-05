	using namespace std;
	
	//STL DESCRIPTORS BASE IMPLEMENTATION
	template<typename Type>
	class StlDescriptor;

	//STRING DESCRIPTOR IMPLEMENTATION
	template<>
	class StlDescriptor< std::string > : public TypedDescriptor<std::string>{
	public:
		StlDescriptor(const std::string& _name, const Uint _size, const Descriptor* _parentDescriptor,
			DescriptorExtension* ext,const std::string& subTypes)
			: TypedDescriptor(_name,_size,_parentDescriptor,ext,subTypes){
				extend();
		}

		static void serialize(void* data,const AbstractSerializer* s){
			std::string& str = *(reinterpret_cast<std::string*>(data));
			s->serialize(str);
		}

	protected:
		void extend(){
			CLASS_SCRIPT(name,string,NoType);
			//ATTRIBUTE ...
		}
	};


	//VECTOR DESCRIPTOR IMPLEMENTATION
	template<typename Type>
	class StlDescriptor< std::vector<Type> > : public TypedDescriptor<std::vector<Type>, ContainerDescriptor>{
	public:
		static const Descriptor* keyDesc;
		static const Descriptor* valueDesc;
		typedef std::vector<Type> VectorType;
		StlDescriptor< std::vector<Type> >(const std::string& _name, const Uint _size, const Descriptor* _parentDescriptor,
			DescriptorExtension* ext,const std::string& subTypes)
			: TypedDescriptor(_name,_size,_parentDescriptor,ext,subTypes){
			valueDesc = ReflectionManager::getDescriptor<Type>();
			keyDesc = ReflectionManager::getDescriptor<Uint>();
			extend();
		}

		virtual const Descriptor* keyDescriptor(void* data)const{
			return keyDesc;
		}
		virtual const Descriptor* valueDescriptor(void* data)const{
			return valueDesc;
		}
		virtual Uint count(void* data)const{
			VectorType& v = *(reinterpret_cast<VectorType*>(data));
			return (Uint)v.size();
		}
		virtual AbstractObject get(void* data,const AbstractObject& key)const{
			Uint i = *(key.get<Uint>());
			VectorType& v = *(reinterpret_cast<VectorType*>(data));
			return AbstractObject(&v[i],valueDesc);
		}
		virtual void insert(void* data,const AbstractObject& key, const AbstractObject& value)const{
			Uint i = *(key.get<Uint>());
			VectorType& v = *(reinterpret_cast<VectorType*>(data));
			VectorType::iterator itInsert = v.begin() + i;
			if(value.isValid() && value.isKindOf<Type>()){
				Type& inserted = *(v.insert(itInsert,*(value.get<Type>())));
				//return AbstractObject(&inserted,valueDesc);
			}
			else{
				Type& inserted = *(v.insert(v.end(),Type()));
				//return AbstractObject(&inserted,valueDesc);
			}
		}
		virtual void remove(void* data,const AbstractObject& key)const{
			Uint i = *(key.get<Uint>());
			VectorType& v = *(reinterpret_cast<VectorType*>(data));
			VectorType::iterator itRemove = v.begin() + i;
			if(itRemove != v.end()){
				v.erase(itRemove);
				//return true;
			}
			//return false;
		}
		static void serialize(void* data,const AbstractSerializer* s){
			VectorType& v = *(reinterpret_cast<VectorType*>(data));
			Uint count = (Uint)v.size();
			s->serialize(count);
			if(s->isLoading()){
				v.reserve(count);
				for(Uint i=0;i<count;++i){
					Type t;
					valueDesc->extension->serialize(&t,s);//Direct Value serialization
					v.push_back(t);
				}
			}
			else{
				for(Uint i=0;i<count;++i){
					Type& t = v[i];
					valueDesc->extension->serialize(&t,s);//Direct Value serialization
				}
			}
		}

		void extend(){
			CLASS_SCRIPT(name,vector<Type>,NoType);
			//ATTRIBUTE ...
		}
	};

	template<typename Type>
	const Descriptor* StlDescriptor< std::vector<Type> >::keyDesc = 0;
	template<typename Type>
	const Descriptor* StlDescriptor< std::vector<Type> >::valueDesc = 0;


	//MAP DESCRIPTOR IMPLEMENTATION
	template<typename KeyType,typename ValueType>
	class StlDescriptor< std::map<KeyType,ValueType> > : public TypedDescriptor<std::map<KeyType,ValueType>, ContainerDescriptor>{
	public:
		static const Descriptor* keyDesc;
		static const Descriptor* valueDesc;
		typedef std::map<KeyType,ValueType> MapType;
		StlDescriptor< std::map<KeyType,ValueType> >(const std::string& _name, const Uint _size, const Descriptor* _parentDescriptor,
			DescriptorExtension* ext,const std::string& subTypes)
			: TypedDescriptor(_name,_size,_parentDescriptor,ext,subTypes){
			valueDesc = ReflectionManager::getDescriptor<ValueType>();
			keyDesc = ReflectionManager::getDescriptor<KeyType>();
			extend();
		}

		virtual const Descriptor* keyDescriptor(void* data)const{
			return keyDesc;
		}
		virtual const Descriptor* valueDescriptor(void* data)const{
			return valueDesc;
		}
		virtual Uint count(void* data)const{
			MapType& v = *(reinterpret_cast<MapType*>(data));
			return (Uint)v.size();
		}
		virtual AbstractObject get(void* data,const AbstractObject& key)const{
			KeyType& k = *(key.get<KeyType>());
			MapType& v = *(reinterpret_cast<MapType*>(data));
			return AbstractObject(&v[k],valueDesc);
		}
		virtual void insert(void* data,const AbstractObject& key, const AbstractObject& value)const{
			KeyType& k = *(key.get<KeyType>());
			MapType& v = *(reinterpret_cast<MapType*>(data));
			if(value.isValid() && value.isKindOf<ValueType>()){
				ValueType& inserted = v[k] = *(value.get<ValueType>());
			}
			else{
				//ASSERT
			}
		}
		virtual void remove(void* data,const AbstractObject& key)const{
			KeyType& k = *(key.get<KeyType>());
			MapType& v = *(reinterpret_cast<MapType*>(data));
			MapType::iterator itRemove = v.find(k);
			if(itRemove != v.end()){
				v.erase(itRemove);
				//return true;
			}
			//return false;
		}

		static void serialize(void* data,const AbstractSerializer* s){
			MapType& v = *(reinterpret_cast<MapType*>(data));
			Uint count = (Uint)v.size();
			s->serialize(count);
			if(s->isLoading()){
				for(Uint i=0;i<count;++i){
					KeyType k;
					keyDesc->extension->serialize(&k,s);//Direct Value serialization
					ValueType t;
					valueDesc->extension->serialize(&t,s);//Direct Value serialization
					v[k] = t;
				}
			}
			else{
				for(MapType::iterator it = v.begin(); it != v.end(); ++it){
					KeyType& k = const_cast<KeyType&>(it->first);
					keyDesc->extension->serialize(&k,s);//Direct Value serialization
					ValueType& t = it->second;
					valueDesc->extension->serialize(&t,s);//Direct Value serialization
				}
			}
		}

		void extend(){
			TEMPLATE_CLASS_SCRIPT(name,std::map,NoType,KeyType,ValueType);
			//ATTRIBUTE ...
		}
	};

	template<typename KeyType,typename ValueType>
	const Descriptor* StlDescriptor< std::map<KeyType,ValueType>  >::keyDesc = 0;
	template<typename KeyType,typename ValueType>
	const Descriptor* StlDescriptor< std::map<KeyType,ValueType>  >::valueDesc = 0;

	//STL DESCRIPTOR DECLARATION MACROS
	#define STL_CLASS(name)\
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
	protected:\
		static void _buildDescriptor(){\
			if(!descriptor){\
				DescriptorExtension* ext = new DescriptorExtension();\
				descriptor = \
					new StlDescriptor<name>(#name,sizeof(name),0,ext,"");\
				ext->registerSerialize("serialize",&StlDescriptor<name>::serialize);\
				ReflectionManager::getInstance()->registerDescriptor(descriptor);\
			}\
		}\
		static Descriptor* descriptor;\
	}

	#define STL_CLASS_IMP(name)\
		Descriptor* DescriptorRetriever<name>::descriptor = 0

	#define STL_TEMPLATE_CLASS(name,T)\
	template<typename T>\
	class DescriptorRetriever< name< T> >{\
	public:\
		typedef name< T > InterestType;\
		static const Descriptor* getDescriptor(){\
			_buildDescriptor();\
			return descriptor;\
		}\
		static const Descriptor* getDescriptor(InterestType* o){\
			_buildDescriptor();\
			return descriptor;\
		}\
	protected:\
		static void _buildDescriptor(){\
			if(!descriptor){\
				DescriptorExtension* ext = new DescriptorExtension();\
				descriptor = \
					new StlDescriptor< InterestType >(#name,sizeof(InterestType),0,ext,TypeNameConcatenator<T>::get());\
				ext->registerSerialize("serialize",&StlDescriptor< InterestType >::serialize);\
				ReflectionManager::getInstance()->registerDescriptor(descriptor);\
			}\
		}\
		static Descriptor* descriptor;\
	};\
	template<typename T>\
	Descriptor* DescriptorRetriever< name< T> >::descriptor = 0


	#define STL_TEMPLATE_CLASS2(name,type1,type2)\
	template<typename type1,typename type2>\
	class DescriptorRetriever< name< type1,type2> >{\
	public:\
		typedef name< type1,type2 > InterestType;\
		static const Descriptor* getDescriptor(){\
			_buildDescriptor();\
			return descriptor;\
		}\
		static const Descriptor* getDescriptor(InterestType* o){\
			_buildDescriptor();\
			return descriptor;\
		}\
	protected:\
		static void _buildDescriptor(){\
			if(!descriptor){\
				DescriptorExtension* ext = new DescriptorExtension();\
				descriptor = \
					new StlDescriptor< InterestType >(#name,sizeof(InterestType),0,ext,TypeNameConcatenator<type1,type2>::get());\
				ext->registerSerialize("serialize",&StlDescriptor< InterestType >::serialize);\
				ReflectionManager::getInstance()->registerDescriptor(descriptor);\
			}\
		}\
		static Descriptor* descriptor;\
	};\
	template<typename type1,typename type2>\
	Descriptor* DescriptorRetriever< name< type1,type2> >::descriptor = 0

	STL_CLASS(string);
	STL_TEMPLATE_CLASS(vector,ValueType);
	STL_TEMPLATE_CLASS2(map,KeyType,ValueType);
