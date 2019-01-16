CLASS_IMP(ActionController_Qt);
	IMPLEMENTATION_OVERLOAD(kQtImplementation,ActionControllerImplementation);
CLASS_END;

ActionController_Qt::ActionController_Qt(){
	actionInnerData().action.initialize(this);
}

void ActionController_Qt::update(){
	if(controller){
		actionInnerData().action.setText(controller->getTitle().c_str());
		actionInnerData().action.setIcon(IconManager_Qt::getIcon(controller->getIconPath()));
		actionInnerData().action.setEnabled(controller->getEnabled());
		actionInnerData().action.setVisible(controller->getVisible());
	}
}

Action_Qt::Action_Qt()
	: QAction(0){
	connect(this, SIGNAL(hovered()), this, SLOT(_hovered()));
	connect(this, SIGNAL(triggered(bool)), this, SLOT(_triggered(bool)));
}

void Action_Qt::initialize(ActionController_Qt * c){
	controller = c;
}

void Action_Qt::_hovered(){
	if(controller && controller->controller){
		controller->controller->hovered();
	}
}

void Action_Qt::_triggered( bool checked ){
	if(controller && controller->controller){
		controller->controller->triggered(checked);
	}
}

#include "moc_ActionController_Qt.cpp"