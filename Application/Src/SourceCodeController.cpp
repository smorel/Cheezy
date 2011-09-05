
CLASS_IMP(SourceCodeController);
	FUNCTION(&SourceCodeController::set);
CLASS_END;

void SourceCodeController::set(const ProxyList& selection){
	ProxyList filtered;
	Proxys::filter<LuaScript>(selection,filtered);
	if(filtered.size() == 1){
		impInnerData().imp->set(filtered[0].get().get<LuaScript>());
	}
}

void* SourceCodeController::getView()const{
	return impInnerData().imp->getView();
}


CLASS_IMP(SourceCodeControllerImplementation);
CLASS_END;
