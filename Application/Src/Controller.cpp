CLASS_IMP(Controller);
	FUNCTION(&Controller::setParent);
	FUNCTION(&Controller::getParent);
CLASS_END;

CLASS_IMP(ContainerController);
	CLASS_VALIDATE(&ContainerController::validate);
	ATTRIBUTE_ADD_REMOVE(subControllers,&ContainerController::addSubController,&ContainerController::removeSubController);
CLASS_END;

void ContainerController::addSubController(const SubController& c, Integer i){
	SubController& res = *subControllers.insert((i < 0) ? subControllers.end() : (subControllers.begin() + i), c);
	res->setParent(this);

	_onAddSubController(c, i);
}

void ContainerController::removeSubController(Integer i){
	SubController& res = subControllers[i];
	_onRemoveSubController(res);

	res->setParent(0);
	subControllers.erase(subControllers.begin() + i);
}

void ContainerController::validate(){
	for(SubControllers::size_type i=0; i<subControllers.size(); ++i){
		SubController& c = subControllers[i];
		if(c){
			c->setParent(this);
			_onAddSubController(c,i);
		}
	}
}

void ContainerController::showSubContainers(){
	for(SubControllers::size_type i=0; i<subControllers.size(); ++i){
		SubController& c = subControllers[i];
		if(c){
			c->show();
		}
	}
}

ENUM_IMP(EOrientation);

CLASS_IMP(SplitterController);
	ATTRIBUTE(orientation);
CLASS_END;

void* SplitterController::getView() const{
	return impInnerData().imp->getView();
}

CLASS_IMP(SplitterControllerImplementation);
CLASS_END;

CLASS_IMP(TabController);
	ATTRIBUTE(orientation);
CLASS_END;

void* TabController::getView() const{
	return impInnerData().imp->getView();
}

CLASS_IMP(TabControllerImplementation);
CLASS_END;
