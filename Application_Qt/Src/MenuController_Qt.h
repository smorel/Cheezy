#pragma once

class MenuController_Qt : public MenuControllerImplementation{
	CLASS(MenuController_Qt,MenuControllerImplementation);
public:
	MenuController_Qt();
	QMenu* getMenu() const { return &menuInnerData().menu; }

protected:
	virtual void update();
	virtual void add(MenuController* m, Controller* before);
	virtual void add(ActionController* a, Controller* before);
	virtual void remove(MenuController* m);
	virtual void remove(ActionController* a);
	virtual void popup();

protected:
	class InnerData{
	public:
		QMenu menu;
		std::map<Controller*,QAction*> controllerToQAction;
	};
	NoCopy<InnerData> menuInnerData;
};