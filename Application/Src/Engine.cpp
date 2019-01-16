CLASS_IMP(Engine);
CLASS_END;

Engine::Engine(){
	//Force link with all dependent libraries ...
	linkCore();
	linkRuntime();
	linkImplement();
	linkDelegate();
	linkUnitTest();
	linkObject();
	linkObjectContext();
	linkSerialization();
	linkFlowChart();
}

void Engine::update(){
	std::clock_t storedClock = innerData().lastTickTime;
	innerData().lastTickTime = std::clock();

	if(!isStarted() || isPaused())
		return;

	std::clock_t diff = innerData().lastTickTime - storedClock;
	innerData().currentTime += diff;

	Uint elapsedTime = (Uint)((diff  / (double)CLOCKS_PER_SEC ) * 1000.0f);
	Uint totalTime = (Uint)((innerData().currentTime  / (double)CLOCKS_PER_SEC ) * 1000.0f);
	_update(totalTime,elapsedTime);
}

void Engine::start(){
	innerData().lastTickTime = clock();
	innerData().currentTime = 0;
	innerData().started = true;
}

void Engine::stop(){
	innerData().started = false;
}

void Engine::pause(Boolean bo){
	innerData().paused = bo;
}