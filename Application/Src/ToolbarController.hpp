class ToolbarController;
class ToolbarControllerImplementation;
typedef Implement<ToolbarController,ToolbarControllerImplementation,ContainerController> ToolbarControllerBase;

class ToolbarControllerImplementation : public ToolbarControllerBase::Implementation{
	CLASS(ToolbarControllerImplementation);
	
protected:
	virtual void add(ActionController* a, Controller* before){};
	virtual void remove(ActionController* a){};
	friend class ToolbarController;
};

class ToolbarController : public ToolbarControllerBase{
	CLASS(ToolbarController,ContainerController);
public:
	ToolbarController();
	
protected:
	virtual void _onAddSubController(const SubController& c, Integer index);
	virtual void _onRemoveSubController(const SubController& c);
};