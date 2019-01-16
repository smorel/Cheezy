#pragma once

class TabController_Qt : public TabControllerImplementation{
	CLASS(TabController_Qt,TabControllerImplementation);
public:
	TabController_Qt();

	virtual void add(Controller* c, Integer i);
	virtual void remove(Controller* c);
	virtual void* getView() const { return &tabInnerData().tab; }

protected:
	class InnerData{
	public:
		QTabWidget tab;
	};
	NoCopy<InnerData> tabInnerData;
};