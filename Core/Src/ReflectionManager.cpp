
	ReflectionManager::ReflectionManager(){
	}

	ReflectionManager::~ReflectionManager(){
	}

	bool ReflectionManager::registerDescriptor(const Descriptor* descriptor){
		if(!descriptor){
			//Log
			return false;
		}

		ReflectionManager* manager = ReflectionManager::getInstance();

		const std::string& name = descriptor->getName();
		Descriptors::const_iterator itFound = manager->descriptors.find(name);
		if(itFound != manager->descriptors.end()){
			//Log already registered
			return false;
		}

		manager->descriptors[name] = descriptor;
		return true;
	}

	const Descriptor* ReflectionManager::getDescriptor(const std::string& name){
		ReflectionManager* manager = ReflectionManager::getInstance();
		Descriptors::const_iterator itFound = manager->descriptors.find(name);
		if(itFound != manager->descriptors.end()){
			return itFound->second;
		}
		return 0;
	}
