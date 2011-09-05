CLASS_IMP(ActionControllerImplementation);
CLASS_END;

CLASS_IMP(ActionController);
	ATTRIBUTE_GETSET(title,&ActionController::getTitle,&ActionController::setTitle);
	ATTRIBUTE_GETSET(iconPath,&ActionController::getIconPath,&ActionController::setIconPath);
	ATTRIBUTE_GETSET(enabled,&ActionController::getEnabled,&ActionController::setEnabled);
	ATTRIBUTE_GETSET(visible,&ActionController::getVisible,&ActionController::setVisible);
CLASS_END;

ActionController::ActionController()
	: enabled(true),visible(true){
}

void ActionController::setTitle(const std::string& t){
	if(title != t){
		title = t;
		impInnerData().imp->update();
	}
}

void ActionController::setIconPath(const std::string& t){
	if(iconPath != t){
		iconPath = t;
		impInnerData().imp->update();
	}
}

void ActionController::setEnabled(Boolean t){
	if(enabled != t){
		enabled = t;
		impInnerData().imp->update();
	}
}

void ActionController::setVisible(Boolean t){
	if(visible != t){
		visible = t;
		impInnerData().imp->update();
	}
}