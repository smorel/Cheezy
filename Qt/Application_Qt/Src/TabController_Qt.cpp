CLASS_IMP(TabController_Qt);
	IMPLEMENTATION_OVERLOAD(kQtImplementation,TabControllerImplementation);
CLASS_END;

TabController_Qt::TabController_Qt(){
}

void TabController_Qt::add(Controller* t, Integer i){
	QWidget* w = static_cast<QWidget*>(t->getView());
	if(w){
		tabInnerData().tab.insertTab(i,w,t->getName().c_str());
	}
}

void TabController_Qt::remove(Controller* c){
}