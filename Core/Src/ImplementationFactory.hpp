class ImplementationFactory{
public:
	typedef std::map<const Descriptor*, const Descriptor*> Remapping;

	const Descriptor* getRemappedDescriptor(const Descriptor* d) const;
	void registerRemappedDescriptor(const Descriptor* source, const Descriptor* remapped);

protected:
	Remapping remapping;
};


class ImplementationFactoryManager : public Singleton<ImplementationFactoryManager>{
public:
	ImplementationFactoryManager() {
	}

	typedef std::map<std::string,ImplementationFactory*> Factories;

	static const Factories& getFactories() { return getInstance()->factories; }

	template<typename Type>
	static Type* createInstance(){
		const Descriptor* d = ReflectionManager::getDescriptor<Type>();
		const Descriptor* toCreate = 0;
		for(std::set<ImplementationFactory*>::iterator it = getInstance()->currentFactories.begin();
			toCreate == 0 && it != getInstance()->currentFactories.end();++it){
			ImplementationFactory* f = *it;
			toCreate = f->getRemappedDescriptor(d);
		}
		return reinterpret_cast<Type*>(toCreate ? toCreate->allocate() : d->allocate());
	}

	static void registerOverload(const std::string& factoryName,const Descriptor* remapped, const Descriptor* source);
	static void use(const std::string& factoryName, Boolean bo);
protected:
	ImplementationFactory* getOrCreateFactory(const std::string& name);

protected:
	Factories factories;
	std::set<ImplementationFactory*> currentFactories;
};

#define IMPLEMENTATION_OVERLOAD(factoryName, parentType)\
	ImplementationFactoryManager::getInstance()->registerOverload(\
		factoryName,descriptor,ReflectionManager::getDescriptor<parentType>())


template<typename ControllerType, typename ImplementationType,typename ParentType = NoType>
class Implement : public ParentType{
public:
	class Implementation{
	public:
		Implementation() : controller(0){}
	protected:
		ControllerType* controller;
		friend class Implement;
	};

	Implement(){
		_initializeImplementation(impInnerData().imp);
	}

	ImplementationType* operator() () { return impInnerData().imp; }

protected:
	virtual void _initializeImplementation(ImplementationType* imp){
		imp->controller = reinterpret_cast<ControllerType*>(this);
	};

	class InnerData{
	public:
		InnerData(){
			imp = ImplementationFactoryManager::createInstance<ImplementationType>();
		}
		ImplementationType* imp;
	};
	NoCopy<InnerData> impInnerData;
};

template<typename ImplementationType, typename ControllerType>
ImplementationType* implementationCast(ControllerType* o){
	if(!o)
		return 0;

	const Descriptor* dImp = ReflectionManager::getInstance()->getDescriptor((*o)());
	if(dImp && dImp->isKindOf<ImplementationType>()){
		return reinterpret_cast<ImplementationType*>((*o)());
	}
	return 0;
}