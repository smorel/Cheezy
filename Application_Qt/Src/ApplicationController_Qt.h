#pragma once

class ApplicationController_Qt;
class Application_Qt : public QApplication{
	Q_OBJECT;
public:
	Application_Qt();
	void run(ApplicationController_Qt* c);

protected:
	virtual void timerEvent(QTimerEvent *);

protected:
	ApplicationController_Qt* controller;
	IconManager_Qt iconManager;
};

class ApplicationController_Qt : public ApplicationControllerImplementation{
	CLASS(ApplicationController_Qt,ApplicationControllerImplementation);
public:
	ApplicationController_Qt();
	
protected:
	virtual void run();

protected:
	class InnerData{
	public:
		InnerData();
		Application_Qt app;
	};
	NoCopy<InnerData> appInnerData;
	friend class Application_Qt;
};