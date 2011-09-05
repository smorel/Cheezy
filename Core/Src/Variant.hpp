
	class Descriptor;
	class AbstractSerializer;
	class Variant{
		SIMPLE_CLASS(Variant);
	public:
		Variant()
			: adress(0),descriptor(0){
		}

		Variant(const Variant& other)
			: adress(0),descriptor(0){
			set(other.getAdress(),other.descriptor);
		}

		Variant(const AbstractObject& other)
			: adress(0),descriptor(0){
			set(other.adress,other.descriptor);
		}

		template<typename Type>
		Variant(Type& o)
			: adress(0),descriptor(0){
			set(&o,ReflectionManager::getDescriptor<Type>());
		}

		template<typename Type>
		Variant(const Type& o)
			: adress(0),descriptor(0){
			set(&(const_cast<Type&>(o)),ReflectionManager::getDescriptor<Type>());
		}

		template<typename Type>
		Variant(Type* o)
			: adress(0),descriptor(0){
			set(o,ReflectionManager::getDescriptor<Type>());
		}

		Variant(void* a,const Descriptor* d)
			: adress(0),descriptor(0){
			set(a,d);
		}

		template<typename Type>
		Type* get() const{
			if(descriptor && descriptor->isKindOf<Type>()){
				if(descriptor->getSize() > sizeof(void*))
					return reinterpret_cast<Type*>(adress);
				else{
					return reinterpret_cast<Type*>(const_cast<Uint*>(&smallValue));
				}
			}
			return 0;
		}

		void* getAdress() const { 
			if(descriptor->getSize() > sizeof(void*))
				return adress; 
			else{
				return (void*)const_cast<Uint*>(&smallValue);
			}
		}
		const Descriptor* getDescriptor() const { return descriptor; }

	protected:
		void serialize(void* data, const AbstractSerializer* s);
		void set(void* memory,const Descriptor* d);
		void free();

	protected:
		union{
			void* adress;
			Uint  smallValue;//valid for PC ... check sizeof(void*) for other 
			//platform and adapt Uint to the good type for those platforms
		};
		const Descriptor* descriptor;
	};
