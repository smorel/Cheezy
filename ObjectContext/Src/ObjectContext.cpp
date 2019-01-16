CLASS_IMP(ObjectContext);
CLASS_END;

ObjectContext::ObjectContext()
: storage(0){
}

ObjectContext::ObjectContext(Storage* s)
: storage(s){
}

Boolean ObjectContext::ownObject(const ID& id){
	return hasObject(id) || (storage && storage->ownObject(id));
}

Boolean ObjectContext::hasObject(const ID& id){
	std::map<const ID,Object*>::iterator itFound = objects.find(id);
	return (Boolean)(itFound != objects.end());
}

Object* ObjectContext::getBootstrapObject(Boolean load){
	return storage ? getObject(storage->getBootstrap(),load) : 0;
}

Object* ObjectContext::getObject(const ID& id, Boolean load){
	std::map<const ID,Object*>::iterator itFound = objects.find(id);
	if(itFound != objects.end()){
		Object* o = itFound->second;
		if(o->isKindOf<PlaceHolder>() && load && storage){
			Object* ret = Object::replace(o,storage->loadObject(id));
			registerObject(ret); //will replace placeholder in map
			PlaceHolder::getClassDescriptor()->deallocate(o);
			return ret;
		}
		else if(o->isKindOf<Object>())
			return o;
	}
	else if(storage && storage->ownObject(id)){
		if(load){
			Object* ret = storage->loadObject(id);
			registerObject(ret);
			return ret;
		}
		else{
			PlaceHolder* p = PlaceHolder::allocate();
			p->id = id;
			p->name = storage->getName(id);
			p->type = storage->getDescriptor(id);
			registerObject(p);
			return p;
		}
	}

	return 0;
}

void ObjectContext::registerObject(Object* o){
	//assert id and o is valid !
	objects[o->getId()] = o;
}

void ObjectContext::saveAll(){
	if(storage)
		storage->saveAll();
}