CLASS_IMP(ToolbarController_Qt);
	IMPLEMENTATION_OVERLOAD(kQtImplementation,ToolbarControllerImplementation);
CLASS_END;

ToolbarController_Qt::ToolbarController_Qt(){
}

void ToolbarController_Qt::add(ActionController* a, Controller* before){
	ActionController_Qt* aqt = implementationCast<ActionController_Qt>(a);
	std::map<Controller*,QAction*>::iterator itFound = 
		before ? tbInnerData().controllerToQAction.find(before) : tbInnerData().controllerToQAction.end();
	if(itFound != tbInnerData().controllerToQAction.end()){
		tbInnerData().controllerToQAction[a] = aqt->getAction();
		tbInnerData().toolbar.insertAction(itFound->second,aqt->getAction());
	}
	else{
		tbInnerData().controllerToQAction[a] = aqt->getAction();
		tbInnerData().toolbar.addAction(aqt->getAction());
	}
}

void ToolbarController_Qt::remove(ActionController* a){
}