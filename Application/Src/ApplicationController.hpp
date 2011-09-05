class ApplicationGlobals : public Singleton<ApplicationGlobals>{
public:
	std::string kIconPath;
	std::string kWorkingPath;
};

class ApplicationController;
class ApplicationControllerImplementation;
typedef Implement<ApplicationController,ApplicationControllerImplementation,ContainerController> ApplicationControllerBase;

class ApplicationControllerImplementation : public ApplicationControllerBase::Implementation{
	CLASS(ApplicationControllerImplementation);
protected:
	virtual void run(){};
	friend class ApplicationController;
};

class ApplicationController : public ApplicationControllerBase{
	CLASS(ApplicationController,ContainerController);
public:
	ApplicationController();
	void update();
	void run();

protected:
	UnitTestManager unitTests;//if needed ...
	Engine engine;
};