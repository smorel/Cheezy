class MapDescriptorTest{
	CLASS(MapDescriptorTest);
protected:
	std::map<Integer,std::vector<std::string> > mapTest;
};

CLASS_IMP(MapDescriptorTest);
	ATTRIBUTE(mapTest);
CLASS_END;


MAKE_TEST(LuaScriptManagerUnitTest)
{
	char mydirectory[MAX_PATH] = {""};
	GetCurrentDirectory(MAX_PATH,mydirectory);

	std::string testScriptPath = mydirectory;
	testScriptPath += "\\..\\..\\test.lua";

	LuaScript s;
	s.load(testScriptPath);
	s.execute();
};