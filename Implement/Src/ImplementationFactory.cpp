
const Descriptor* ImplementationFactory::getRemappedDescriptor(const Descriptor* d) const{
	Remapping::const_iterator itFound = remapping.find(d);
	if(itFound != remapping.end()){
		return itFound->second;
	}
	return 0;
}

void ImplementationFactory::registerRemappedDescriptor(const Descriptor* source, const Descriptor* remapped){
	Remapping::const_iterator itFound = remapping.find(source);
	//ASSERT(itFound == remapping.end())
	remapping[source] = remapped;
}


void ImplementationFactoryManager::registerOverload(const std::string& factoryName,
	const Descriptor* remapped, const Descriptor* source){
		ImplementationFactory* factory = getInstance()->getOrCreateFactory(factoryName);
		factory->registerRemappedDescriptor(source,remapped);
}

ImplementationFactory* ImplementationFactoryManager::getOrCreateFactory(const std::string& name){
	Factories::iterator itFound = factories.find(name);
	if(itFound != factories.end())
		return itFound->second;

	ImplementationFactory* newFactory = new ImplementationFactory();
	factories[name] = newFactory;

	return newFactory;
}

void ImplementationFactoryManager::use(const std::string& factoryName, Boolean bo){
	ImplementationFactory* factory = getInstance()->getOrCreateFactory(factoryName);
	if(bo){
		getInstance()->currentFactories.insert(factory);
	}
	else{
		std::set<ImplementationFactory*>::iterator itFound = 
			getInstance()->currentFactories.find(factory);
		if(itFound != getInstance()->currentFactories.end()){
			getInstance()->currentFactories.erase(factory);
		}
	}
}
