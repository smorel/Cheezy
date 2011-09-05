CLASS_IMP(ApplicationControllerImplementation);
CLASS_END;

CLASS_IMP(ApplicationController);
CLASS_END;

ApplicationController::ApplicationController(){
	UnitTestManager::execute();
	engine.start();
}

void ApplicationController::update(){
	engine.update();
}

void ApplicationController::run(){
	showSubContainers();
	impInnerData().imp->run();
}