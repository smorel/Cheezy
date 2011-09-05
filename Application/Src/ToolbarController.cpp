CLASS_IMP(ToolbarControllerImplementation);
CLASS_END;

CLASS_IMP(ToolbarController);
CLASS_END;

ToolbarController::ToolbarController(){
}

void ToolbarController::_onAddSubController(const SubController& c, Integer index){
	std::set<const Descriptor*> descs;
	descs.insert(DESCRIPTOR(ActionController));
	if(c && c->isKindOf<ActionController>()){
		ActionController* a = safeCast<ActionController>(c.get());
		Controller* aBefore = findNextOfType(subControllers,index,descs);
		impInnerData().imp->add(a,aBefore);
	}
}

void ToolbarController::_onRemoveSubController(const SubController& c){
	if(c && c->isKindOf<ActionController>()){
		ActionController* a = safeCast<ActionController>(c.get());
		impInnerData().imp->remove(a);
	}
}