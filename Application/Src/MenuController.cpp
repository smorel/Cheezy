CLASS_IMP(MenuControllerImplementation);
CLASS_END;

CLASS_IMP(MenuController);
	ATTRIBUTE_GETSET(title,&MenuController::getTitle,&MenuController::setTitle);
	ATTRIBUTE_GETSET(iconPath,&MenuController::getIconPath,&MenuController::setIconPath);
	ATTRIBUTE_GETSET(enabled,&MenuController::getEnabled,&MenuController::setEnabled);
CLASS_END;

MenuController::MenuController()
	: enabled(true){
}

void MenuController::setTitle(const std::string& t){
	if(title != t){
		title = t;
		impInnerData().imp->update();
	}
}

void MenuController::setIconPath(const std::string& t){
	if(iconPath != t){
		iconPath = t;
		impInnerData().imp->update();
	}
}

void MenuController::setEnabled(Boolean t){
	if(enabled != t){
		enabled = t;
		impInnerData().imp->update();
	}
}

void MenuController::popup(){
	impInnerData().imp->popup();
}

void MenuController::_onAddSubController(const SubController& c, Integer index){
	std::set<const Descriptor*> descs;
	descs.insert(DESCRIPTOR(MenuController));
	descs.insert(DESCRIPTOR(ActionController));
	if(c && c->isKindOf<MenuController>()){
		MenuController* m = safeCast<MenuController>(c.get());
		Controller* aBefore = findNextOfType(subControllers,index,descs);
		impInnerData().imp->add(m,aBefore);
	}
	else if(c && c->isKindOf<ActionController>()){
		ActionController* a = safeCast<ActionController>(c.get());
		Controller* aBefore = findNextOfType(subControllers,index,descs);
		impInnerData().imp->add(a,aBefore);
	}
}

void MenuController::_onRemoveSubController(const SubController& c){
	if(c && c->isKindOf<MenuController>()){
		MenuController* m = safeCast<MenuController>(c.get());
		impInnerData().imp->remove(m);
	}
	else if(c && c->isKindOf<ActionController>()){
		ActionController* a = safeCast<ActionController>(c.get());
		impInnerData().imp->remove(a);
	}
}