class ActionController;
class ActionControllerImplementation;
typedef Implement<ActionController,ActionControllerImplementation,Controller> ActionControllerBase;

class ActionControllerImplementation : public ActionControllerBase::Implementation
{
	CLASS(ActionControllerImplementation);
protected:
	virtual void update(){};
	friend class ActionController;
};

class ActionController : public ActionControllerBase
{
	CLASS(ActionController,Controller);
public:
	ActionController();

	virtual void hovered(){};
	virtual void triggered(bool bo){};
	
	void setTitle(const std::string& t);
	const std::string& getTitle() const { return title; }
	void setIconPath(const std::string& t);
	const std::string& getIconPath() const { return iconPath; }
	void setEnabled(Boolean t);
	Boolean getEnabled() const { return enabled; }
	void setVisible(Boolean t);
	Boolean getVisible() const { return visible; }

protected:
	std::string title;
	std::string iconPath;
	Boolean enabled;
	Boolean visible;
};