#pragma once

class ToolbarController_Qt : public ToolbarControllerImplementation{
	CLASS(ToolbarController_Qt,ToolbarControllerImplementation);
public:
	ToolbarController_Qt();

	QToolBar* getToolbar() const { return &tbInnerData().toolbar; }

protected:
	virtual void add(ActionController* a, Controller* before);
	virtual void remove(ActionController* a);

protected:
	class InnerData{
	public:
		QToolBar toolbar;
		std::map<Controller*,QAction*> controllerToQAction;
	};
	NoCopy<InnerData> tbInnerData;
};