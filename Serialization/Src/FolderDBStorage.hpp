class FolderDBStorage : public Storage{
	CLASS(FolderDBStorage,Storage);
public:
	FolderDBStorage();
	FolderDBStorage(const std::string& _path);

	class ObjectSerializer{
		CLASS(ObjectSerializer);
	public:
		void save(Object* o,const std::string& path);
		Object* load(const std::string& path);
		Boolean exists(const std::string& path);
	};

public:
	virtual Boolean ownObject(const ID& id);
	virtual Object* loadObject(const ID& id);
	virtual std::string getName(const ID& id);
	virtual const Descriptor* getDescriptor(const ID& id);
	virtual void saveAll();
	virtual void clear();
	void saveObject(Object* o);

protected:
	virtual Boolean _requestEdition(Object* o);
	std::string _filePath(const ID& id);
	std::string _bootstrapPath();
	void _ensureFolderExists();

	void _saveBootstrap();
	void _loadBootstrap();

protected:
	std::string path;
};