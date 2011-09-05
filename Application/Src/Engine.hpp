class Engine : public Singleton<Engine>{
	CLASS(Engine);
public:
	Engine();

	void update();
	void start();
	void stop();
	void pause(Boolean bo = true);

	Boolean isStarted() const { return innerData().started; }
	Boolean isPaused() const { return innerData().paused; }

protected:
	virtual void _update(Uint totalTime, Uint elapsedTime){};

	class InnerData{
	public:
		InnerData() : started(false),paused(false){}
		std::clock_t currentTime;
		std::clock_t lastTickTime;
		Boolean started;
		Boolean paused;

		ImplementationFactoryManager implementationFactory;
		LuaScriptManager luaScriptManager;
		MemoryManager memoryManager;
		ReflectionManager reflectionManager;
		ObjectContextCoordinator contextCoordinator;
	};
	NoCopy<InnerData> innerData;
};