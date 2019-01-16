
class Storage{
	CLASS(Storage);
public:
	Storage(){}

	void setBootstrap(const ID& id){bootstrap = id;}
	void setBootstrap(Object* o){bootstrap = o->getId();}
	const ID& getBootstrap(){return bootstrap;}

	virtual void clear(){}
	virtual Boolean ownObject(const ID& id){return false;}
	virtual Object* loadObject(const ID& id){return 0;}
	virtual std::string getName(const ID& id){return "";}
	virtual const Descriptor* getDescriptor(const ID& id){return 0;}

	//Save editedObjects appropriatly
	virtual void saveAll(){};

	//please register 
	Boolean requestEdition(Object* o){
		Boolean ret = _requestEdition(o);
		if(ret){
			editedObjects.insert(o);
		}
		return ret;
	}

protected:
	virtual Boolean _requestEdition(Object* o){return false;}

protected:
	std::set<Object*> editedObjects;
	ID bootstrap;
};
