	CLASS_IMP(ReferenceConcept);
	CLASS_END;

	CLASS_IMP(ReferenceBase);
		CLASS_CONCEPT(ReferenceConcept);
		CLASS_SERIALIZE(&ReferenceBase::serialize);
	CLASS_END;

	ReferenceBase::ReferenceBase()
		: reference(0){
	}
	
	ReferenceBase::ReferenceBase(Object* o)
		: reference(o){
	}

	
	void ReferenceBase::serialize(void* data, const ISerializer* s){
		if(s->isLoading()){
			ID id = *(s->serialize().get<ID>());
			reference = Object::fetchObject(id);
		}
		else{
			ID id = reference ? reference->getId() : ID();
			s->serialize(AbstractObject(id));
		}
	}
