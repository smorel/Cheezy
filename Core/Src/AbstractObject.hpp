
	class Descriptor;
	class AbstractObject{
	public:
		AbstractObject();
		AbstractObject(const AbstractObject& other);

		static const Descriptor* getClassDescriptor() {
			return NULL;
		}

		template<typename Type>
		AbstractObject(Type& o){
			set(&o,ReflectionManager::getDescriptor<Type>(&o));
		}

		template<typename Type>
		AbstractObject(const Type& o){
			set(&(const_cast<Type&>(o)),ReflectionManager::getDescriptor<Type>(&(const_cast<Type&>(o))));
		}

		template<typename Type>
		AbstractObject(Type* o){
			set((void*)o, ReflectionManager::getDescriptor<Type>(o));
		}

		AbstractObject(void* a,const Descriptor* d){
			set(a,d);
		}

		template<typename Type>
		Type* get() const{
			if(descriptor && descriptor->isKindOf<Type>()){
				return reinterpret_cast<Type*>(adress);
			}
			return 0;
		}

		template<typename Type>
		Boolean isKindOf() const{
			return descriptor && descriptor->isKindOf<Type>();
		}

		void* getAdress() const { return adress; }
		const Descriptor* getDescriptor() const { return descriptor; }

		void set(void* _memory, const Descriptor* _descriptor);

		Boolean isValid() const;

	protected:
		void* adress;
		const Descriptor* descriptor;

		friend class Variant;
	};
