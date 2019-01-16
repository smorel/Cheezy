CLASS_IMP(ObjectContextCoordinator);
CLASS_END;

CLASS_IMP(ObjectContextCoordinator::RequestBase);
CLASS_END;


void ObjectContextCoordinator::fetchRequest(std::vector<RequestBase*>& requests, std::set<Object*>& results){
	ObjectContextCoordinator* coordinator = ObjectContextCoordinator::getInstance();
}

Object* ObjectContextCoordinator::fetchObject(const ID& id){
	ObjectContextCoordinator* coordinator = ObjectContextCoordinator::getInstance();
	for(std::map<std::string,ObjectContext*>::iterator it = coordinator->contexts.begin();it != coordinator->contexts.end(); ++it){
		ObjectContext* o = it->second;
		if(o->ownObject(id))
			return o->getObject(id,true);
	}
	return 0;
}

void ObjectContextCoordinator::registerObjectContext(const std::string& name,ObjectContext* c){
	ObjectContextCoordinator* coordinator = ObjectContextCoordinator::getInstance();
	
	std::map<std::string,ObjectContext*>::iterator itFound = coordinator->contexts.find(name);
	//ASSERT itFound == contexts.end()
	coordinator->contexts[name] = c;
}

ObjectContext* ObjectContextCoordinator::_getObjectContext(const std::string& name){
	std::map<std::string,ObjectContext*>::iterator itFound = contexts.find(name);
	if(itFound != contexts.end()){
		return itFound->second;
	}
	return 0;
}

std::string ObjectContextCoordinator::getObjectContextTag(const ID& id){
	ObjectContextCoordinator* coordinator = ObjectContextCoordinator::getInstance();
	for(std::map<std::string,ObjectContext*>::iterator it = coordinator->contexts.begin();it != coordinator->contexts.end(); ++it){
		ObjectContext* o = it->second;
		if(o->ownObject(id))
			return it->first;
	}
	return "";
}

void ObjectContextCoordinator::saveAll(){
	ObjectContextCoordinator* coordinator = ObjectContextCoordinator::getInstance();
	for(std::map<std::string,ObjectContext*>::iterator it = coordinator->contexts.begin();it != coordinator->contexts.end(); ++it){
		ObjectContext* o = it->second;
		o->saveAll();
	}
}


Object* ObjectContextCoordinator::getBootstrap(const std::string& tag,bool load){
	ObjectContext* c = ObjectContextCoordinator::getInstance()->_getObjectContext(tag);
	return c ? c->getBootstrapObject(load) : 0;
}


Object* Object::fetchObject(const ID& id) {
	return ObjectContextCoordinator::fetchObject(id);
}