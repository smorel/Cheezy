CLASS_IMP(SplitterController_Qt);
	IMPLEMENTATION_OVERLOAD(kQtImplementation,SplitterControllerImplementation);
CLASS_END;

SplitterController_Qt::SplitterController_Qt(){
}

void SplitterController_Qt::add(Controller* t, Integer i){
	QWidget* w = static_cast<QWidget*>(t->getView());
	if(w){
		spInnerData().splitter.insertWidget(i,w);
	}
}

void SplitterController_Qt::remove(Controller* t, Integer i){
}
