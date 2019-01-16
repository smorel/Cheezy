CLASS_IMP(ApplicationController_Qt);
	IMPLEMENTATION_OVERLOAD(kQtImplementation,ApplicationControllerImplementation);
CLASS_END;

ApplicationController_Qt::InnerData::InnerData(){
}

ApplicationController_Qt::ApplicationController_Qt(){
}

void ApplicationController_Qt::run(){
	appInnerData().app.run(this);
}

static int i = 0;
Application_Qt::Application_Qt()
: QApplication(i,0),controller(0){

#ifdef Q_WS_MAC
	QApplication::setStyle(QStyleFactory::create("macintosh"));
#else
	QApplication::setStyle(QStyleFactory::create("windows"));
#endif
}

void Application_Qt::run(ApplicationController_Qt* c){
	controller = c;
	startTimer(1);
	exec();
}

void Application_Qt::timerEvent(QTimerEvent *){
	if(controller && controller->controller){
		controller->controller->update();
	}
}

#include "moc_ApplicationController_Qt.cpp"