CLASS_IMP(MainController_Qt);
	IMPLEMENTATION_OVERLOAD(kQtImplementation,MainControllerImplementation);
CLASS_END;

MainController_Qt::MainController_Qt(){
	wndInnerData().mainWindow.initialize(this);
}

void MainController_Qt::show(bool maximized){
	if(maximized){
		wndInnerData().mainWindow.showMaximized();
	}
	else{
		wndInnerData().mainWindow.show();
	}
}

void MainController_Qt::add(ToolbarController* t){
	ToolbarController_Qt* tqt = implementationCast<ToolbarController_Qt>(t);
	wndInnerData().mainWindow.addToolBar(tqt->getToolbar());
}

void MainController_Qt::add(MenuController* m, MenuController* before){
	MenuController_Qt* mqt = implementationCast<MenuController_Qt>(m);
	std::map<Controller*,QAction*>::iterator itFound = 
		before ? wndInnerData().controllerToQAction.find(before) : wndInnerData().controllerToQAction.end();
	if(itFound != wndInnerData().controllerToQAction.end()){
		wndInnerData().controllerToQAction[m] =
			wndInnerData().mainWindow.menuBar.insertMenu(itFound->second,mqt->getMenu());
	}
	else{
		wndInnerData().controllerToQAction[m] =
			wndInnerData().mainWindow.menuBar.addMenu(mqt->getMenu());
	}
}

void MainController_Qt::add(Controller* t, Integer i){
	QWidget* w = static_cast<QWidget*>(t->getView());
	if(w){
		wndInnerData().mainWindow.layout.insertWidget(i,w);
	}
}

void MainController_Qt::remove(ToolbarController* t){
}

void MainController_Qt::remove(MenuController* t){
}

void MainController_Qt::remove(Controller* t){
}

MainWindow_Qt::MainWindow_Qt(){
	centralWidget.setLayout(&layout);
	setCentralWidget(&centralWidget);
	setMenuBar(&menuBar);
}

void MainWindow_Qt::initialize(MainController_Qt* c){
	controller = c;
}


#include "moc_MainController_Qt.cpp"