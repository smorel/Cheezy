	class ReferenceConcept{
			CLASS(ReferenceConcept);
	};

	class ReferenceBase{
		CLASS(ReferenceBase);
	public:
		ReferenceBase();
		ReferenceBase(Object* o);

		virtual void serialize(void* data, const ISerializer* s);

		Boolean isNull() const { return reference == 0; }

	protected:
		Object* reference;
	};

	template<typename Type>
	class Reference : public ReferenceBase{
		TEMPLATE_CLASS(Reference<Type>,ReferenceBase);

	public:
		Reference() : ReferenceBase(){
		}

		Reference(Type* o) :ReferenceBase(o){
		}

		Reference& operator=(Type* t){
			reference = t;
			return *this;
		}

		Type* get() const { 
			return safeCast<Type>(reference); 
		}

		Type* operator->() const{
			return safeCast<Type>(reference);
		}

		Type& operator*() const {
            return *reference;
        }

		operator bool() const{
			return reference != 0;
		}
		
		TEMPLATE_CLASS_IMP(Reference,Type);
			CLASS_SERIALIZE(&ReferenceBase::serialize);
		CLASS_END;
	};

	template<typename ReferenceType>
	ReferenceType* findPreviousOfType(const std::vector< Reference<ReferenceType> >& v, Integer index,
		const std::set<const Descriptor*>& descs){
		for(std::vector< Reference<ReferenceType> >::size_type i = max(index,0)-1; i >= 0; --i){
			const Reference<ReferenceType>& r = v[i];
			for(std::set<const Descriptor*>::const_iterator it = descs.begin(); it != descs.end(); ++it){
				const Descriptor* d = *it;
				if(r && r->isKindOf(d)){
					return r.get();
				}
			}
		}
		return 0;
	}

	template<typename Type, typename ReferenceType>
	Type* findPreviousOfType(const std::vector< Reference<ReferenceType> >& v, Integer index){
		for(std::vector< Reference<ReferenceType> >::size_type i = max(index,0)-1; i >= 0; --i){
			const Reference<ReferenceType>& r = v[i];
			if(r && r->isKindOf<Type>()){
				return reinterpret_cast<Type*>(r.get());
			}
		}
		return 0;
	}

	template<typename ReferenceType>
	ReferenceType* findNextOfType(const std::vector< Reference<ReferenceType> >& v, Integer index,
		const std::set<const Descriptor*>& descs){
		for(std::vector< Reference<ReferenceType> >::size_type i = max(index,0)+1; i < v.size(); ++i){
			const Reference<ReferenceType>& r = v[i];
			for(std::set<const Descriptor*>::const_iterator it = descs.begin(); it != descs.end(); ++it){
				const Descriptor* d = *it;
				if(r && r->isKindOf(d)){
					return r.get();
				}
			}
		}
		return 0;
	}

	template<typename Type, typename ReferenceType>
	Type* findNextOfType(const std::vector< Reference<ReferenceType> >& v, Integer index = 0){
		for(std::vector< Reference<ReferenceType> >::size_type i = max(index,0)+1; i < v.size(); ++i){
			const Reference<ReferenceType>& r = v[i];
			if(r && r->isKindOf<Type>()){
				return reinterpret_cast<Type*>(r.get());
			}
		}
		return 0;
	}
