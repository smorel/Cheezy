	class MemoryManager : public Singleton<MemoryManager>{
	public:
		const std::set<std::string>& getCategories() const {return categories;}

		void* allocate(Uint size, const std::string& category);
		void deallocate(void* memory,const std::string& category);

		template<typename Type>
		Type* allocate(const std::string& category){
			initializeCategory(category);
			Type* ret = new Type();
			registerNew(sizeof(ret),category);
			return ret;
		}

		template<typename Type>
		void deallocate(void* memory,const std::string& category){
			unregisterNew(sizeof(memory),category);
			delete memory;
			memory = 0;
		}

	protected:
		void initializeCategory(const std::string& category);
		void registerNew(Uint size,const std::string& category);
		void unregisterNew(Uint size,const std::string& category);

	protected:
		std::set<std::string> categories;
		std::map<std::string,Uint> categoryConsumption;
		std::map<std::string,Uint> categoryObjectCount;
	};
