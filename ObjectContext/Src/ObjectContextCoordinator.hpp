//Fetch request manager
//save, load manager
//create object manager
class ObjectContextCoordinator : public Singleton<ObjectContextCoordinator>{
	CLASS(ObjectContextCoordinator);
public:
	class RequestBase{
		CLASS(RequestBase);
	};

	static Object* fetchObject(const ID& id);
	static void fetchRequest(std::vector<RequestBase*>& requests, std::set<Object*>& results);

	static void registerObjectContext(const std::string& tag,ObjectContext* c);
	
	template<typename Type>
	static Type* allocate(const std::string& contextName){
		ObjectContextCoordinator* coordinator = ObjectContextCoordinator::getInstance();
		ObjectContext* c = coordinator->_getObjectContext(contextName);
		if(c){
			return c->allocate<Type>();
		}
		return 0;
	}

	static Object* getBootstrap(const std::string& tag,bool load = false);

	static std::string getObjectContextTag(const ID& id);
	static void saveAll();

protected:
	ObjectContext* _getObjectContext(const std::string& name);

protected:
	std::map<std::string,ObjectContext*> contexts;
};
