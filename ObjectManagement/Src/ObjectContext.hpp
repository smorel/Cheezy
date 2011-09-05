class Storage;
class ObjectContext{
	CLASS(ObjectContext);
public:
	ObjectContext();
	ObjectContext(Storage* s);

	//is loaded in the context or available in the storage
	Boolean ownObject(const ID& id);
	//is loaded in the context
	Boolean hasObject(const ID& id);
	//retrieve the object
	Object* getObject(const ID& id, Boolean load = false);
	Object* getBootstrapObject(Boolean load = false);

	template<typename Type>
	Type* allocate(){
		Type* instance = 0;
		const Descriptor* d = ReflectionManager::getInstance()->getDescriptor<Type>();
		if(d->isKindOf<Object>()){
			instance = reinterpret_cast<Type*>(d->allocate());
			instance->id = ID::create();
			registerObject(instance);
			if(storage){
				storage->requestEdition(instance);
			}
		}
		return instance;
	}

	void registerObject(Object* o);
	void saveAll();

protected:
	Storage* storage;
	std::map<const ID,Object*> objects;
};
