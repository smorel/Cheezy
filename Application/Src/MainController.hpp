class MainController;
class MainControllerImplementation;
typedef Implement<MainController,MainControllerImplementation,ContainerController> MainControllerBase;

class ToolbarController;
class MenuController;
class MainControllerImplementation : public MainControllerBase::Implementation
{
	CLASS(MainControllerImplementation);
protected:
	virtual void show(bool maximized = true){};

	virtual void add(ToolbarController* t){};
	virtual void add(MenuController* t, MenuController* before){};
	virtual void add(Controller* t, Integer i){};
	
	virtual void remove(ToolbarController* t){};
	virtual void remove(MenuController* t){};
	virtual void remove(Controller* t){}; 
	
	virtual void* getView()const{return 0;}

	friend class MainController;
};

class MainController : public MainControllerBase
{
	CLASS(MainController,ContainerController);
public:
	MainController();
	
	virtual void show();
	void validate();
	
	virtual void* getView()const;

protected:
	virtual void _onAddSubController(const SubController& c, Integer index);
	virtual void _onRemoveSubController(const SubController& c);

	//Toolbars && menus will be subControllers
};