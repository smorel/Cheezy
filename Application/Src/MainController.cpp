CLASS_IMP(MainControllerImplementation);
CLASS_END;

CLASS_IMP(MainController);
CLASS_END;

MainController::MainController(){
}

void MainController::show(){
	impInnerData().imp->show();
}

void* MainController::getView()const{
	return impInnerData().imp->getView();
}

void MainController::_onAddSubController(const SubController& c, Integer index){
	if(c && c->isKindOf<ToolbarController>()){
		ToolbarController* t = safeCast<ToolbarController>(c.get());
		impInnerData().imp->add(t);
	}
	else if(c && c->isKindOf<MenuController>()){
		MenuController* m = safeCast<MenuController>(c.get());
		MenuController* mBefore = findNextOfType<MenuController>(subControllers,index);
		impInnerData().imp->add(m,mBefore);
	}
	else if(c){
		impInnerData().imp->add(c.get(),index);
	}
}

void MainController::_onRemoveSubController(const SubController& c){
	if(c && c->isKindOf<ToolbarController>()){
		ToolbarController* t = safeCast<ToolbarController>(c.get());
		impInnerData().imp->remove(t);
	}
	else if(c && c->isKindOf<MenuController>()){
		MenuController* m = safeCast<MenuController>(c.get());
		impInnerData().imp->remove(m);
	}
	else if(c){
		impInnerData().imp->remove(c.get());
	}
}