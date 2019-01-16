CLASS_IMP(MenuController_Qt);
	IMPLEMENTATION_OVERLOAD(kQtImplementation,MenuControllerImplementation);
CLASS_END;

MenuController_Qt::MenuController_Qt(){
}

void MenuController_Qt::update(){
	if(controller){
		menuInnerData().menu.setTitle(controller->getTitle().c_str());
		menuInnerData().menu.setIcon(IconManager_Qt::getIcon(controller->getIconPath()));
		menuInnerData().menu.setEnabled(controller->getEnabled());
	}
}

void MenuController_Qt::add(MenuController* m, Controller* before){
	MenuController_Qt* mqt = implementationCast<MenuController_Qt>(m);
	std::map<Controller*,QAction*>::iterator itFound = 
		before ? menuInnerData().controllerToQAction.find(before) : menuInnerData().controllerToQAction.end();
	if(itFound != menuInnerData().controllerToQAction.end()){
		menuInnerData().controllerToQAction[m] =
			menuInnerData().menu.insertMenu(itFound->second,mqt->getMenu());
	}
	else{
		menuInnerData().controllerToQAction[m] =
			menuInnerData().menu.addMenu(mqt->getMenu());
	}
}

void MenuController_Qt::add(ActionController* a, Controller* before){
	ActionController_Qt* aqt = implementationCast<ActionController_Qt>(a);
	std::map<Controller*,QAction*>::iterator itFound = 
		before ? menuInnerData().controllerToQAction.find(before) : menuInnerData().controllerToQAction.end();
	if(itFound != menuInnerData().controllerToQAction.end()){
		menuInnerData().controllerToQAction[a] = aqt->getAction();
		menuInnerData().menu.insertAction(itFound->second,aqt->getAction());
	}
	else{
		menuInnerData().controllerToQAction[a] = aqt->getAction();
		menuInnerData().menu.addAction(aqt->getAction());
	}
}

void MenuController_Qt::remove(MenuController* m){
}

void MenuController_Qt::remove(ActionController* a){
}

void MenuController_Qt::popup(){
	QAction* res = menuInnerData().menu.exec(QCursor::pos());
}