class MenuController;
class MenuControllerImplementation;
typedef Implement<MenuController,MenuControllerImplementation,ContainerController> MenuControllerBase;

class MenuControllerImplementation : public MenuControllerBase::Implementation
{
	CLASS(MenuControllerImplementation);
protected:
	virtual void update(){};
	virtual void add(MenuController* m, Controller* before){};
	virtual void add(ActionController* a, Controller* before){};
	virtual void remove(MenuController* m){};
	virtual void remove(ActionController* a){};
	virtual void popup(){};

	friend class MenuController;
};

class MenuController : public MenuControllerBase
{
	CLASS(MenuController,ContainerController);
public:
	MenuController();

	void setTitle(const std::string& t);
	const std::string& getTitle() const { return title; }
	void setIconPath(const std::string& t);
	const std::string& getIconPath() const { return iconPath; }
	void setEnabled(Boolean t);
	Boolean getEnabled() const { return enabled; }

	void popup();
	
protected:
	virtual void _onAddSubController(const SubController& c, Integer index);
	virtual void _onRemoveSubController(const SubController& c);

protected:
	std::string title;
	std::string iconPath;
	Boolean enabled;
};