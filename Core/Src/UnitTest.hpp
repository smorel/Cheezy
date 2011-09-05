class UnitTest;
class UnitTestManager : public Singleton<UnitTestManager>{
public:
	UnitTestManager(){
	}

	static Boolean registerTest(UnitTest* test){
		UnitTestManager::getInstance()->tests.push_back(test);
		return true;
	}
	static void execute();
	static void execute(const std::string& beginWith);
protected:
	std::vector<UnitTest*> tests;
	friend class UnitTest;
};

	class UnitTest {
	public:
		UnitTest(const std::string& n) : name(n){
		}

		virtual void execute() = 0;
		std::string name;
	};


#define MAKE_TEST(TestName) \
	class TestName : public UnitTest { \
	public: \
		virtual void execute(); \
		TestName() : UnitTest(#TestName) { } \
	protected:\
		static Boolean registerBool;\
	}; \
	Boolean TestName::registerBool = UnitTestManager::registerTest(new TestName()); \
	void TestName::execute()
