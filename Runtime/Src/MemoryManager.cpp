
	void* MemoryManager::allocate(Uint size, const std::string& category){
		initializeCategory(category);
		void* ret = malloc(size);
		registerNew(sizeof(ret),category);
		return ret;
	}

	void MemoryManager::deallocate(void* memory,const std::string& category){
		unregisterNew(sizeof(memory),category);
		free(memory);
	}
	
	void MemoryManager::registerNew(Uint size,const std::string& category){
		categoryConsumption[category] += size;
		categoryObjectCount[category]++;
	}

	void MemoryManager::unregisterNew(Uint size,const std::string& category){
		categoryConsumption[category] -= size;
		categoryObjectCount[category]--;
	}
	
	void MemoryManager::initializeCategory(const std::string& category){
		{
			std::set<std::string>::iterator itFound = categories.find(category);
			if(itFound == categories.end()){
				categories.insert(category);
			}
		}

		{
			std::map<std::string,Uint>::iterator itFound = categoryConsumption.find(category);
			if(itFound == categoryConsumption.end()){
				categoryConsumption[category] = 0;
			}
		}

		{
			std::map<std::string,Uint>::iterator itFound = categoryObjectCount.find(category);
			if(itFound == categoryObjectCount.end()){
				categoryObjectCount[category] = 0;
			}
		}
	}
