#pragma once

class MainController_Qt;
class MainWindow_Qt : public QMainWindow{
	Q_OBJECT;

public:
	MainWindow_Qt();
	void initialize(MainController_Qt* c);

protected:
	QHBoxLayout layout;
	QWidget centralWidget;
	QMenuBar menuBar;
	MainController_Qt* controller;

	friend class MainController_Qt;
};


class MenuController_Qt;
class MainController_Qt : public MainControllerImplementation{
	CLASS(MainController_Qt,MainControllerImplementation);
public:
	MainController_Qt();

	virtual void* getView() const { return &wndInnerData().mainWindow.centralWidget; }

protected:
	virtual void show(bool maximized = true);
	
	virtual void add(ToolbarController* t);
	virtual void add(MenuController* t, MenuController* before);
	virtual void add(Controller* t, Integer i);
	
	virtual void remove(ToolbarController* t);
	virtual void remove(MenuController* t);
	virtual void remove(Controller* t);

protected:
	class InnerData{
	public:
		MainWindow_Qt mainWindow;
		std::map<Controller*,QAction*> controllerToQAction;
	};
	NoCopy<InnerData> wndInnerData;
};