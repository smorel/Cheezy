int main(int argc, char *argv[])
{
	linkApplicationQt();
	ImplementationFactoryManager::use("Qt",true);

	char mydirectory[MAX_PATH] = {""};
	GetCurrentDirectory(MAX_PATH,mydirectory);

	//All the following should be able to be done in a tool or script ;)

	ApplicationGlobals::getInstance()->kWorkingPath = mydirectory;
	ApplicationGlobals::getInstance()->kWorkingPath += "\\";
	ApplicationGlobals::getInstance()->kIconPath = mydirectory;
	ApplicationGlobals::getInstance()->kIconPath += "\\..\\..\\Icons\\";

	ApplicationController appController;

	MainController mainController;
	appController.addSubController(&mainController);
	
	MenuController menu1;
	menu1.setTitle("MenuTest");
	menu1.setIconPath("MenuTest.png");
	mainController.addSubController(&menu1);
	
	ActionController action1;
	action1.setTitle("ActionTest");
	action1.setIconPath("ActionTest.png");
	//action1.setVisible(false);
	menu1.addSubController(&action1);
	
	MenuController submenu1;
	submenu1.setTitle("SubMenuTest");
	submenu1.setIconPath("SubMenuTest.png");
	menu1.addSubController(&submenu1);

	ActionController action2;
	action2.setTitle("ActionTest2");
	action2.setIconPath("ActionTest2.png");
	action2.setEnabled(false);
	submenu1.addSubController(&action2);
	
	ToolbarController toolbar1;
	toolbar1.addSubController(&action1);
	toolbar1.addSubController(&action2);
	mainController.addSubController(&toolbar1);

	SplitterController baseSplit;

	SplitterController split1;
	split1.setName("hallo");
	SplitterController split2;
	split2.setName("cool");
	TabController tab;
	tab.addSubController(&split1);
	tab.addSubController(&split2);

	SourceCodeController sourceCode;
	sourceCode.setName("Source Code");
	
	TabController tab2;
	tab2.addSubController(&sourceCode);
	baseSplit.addSubController(&tab);
	baseSplit.addSubController(&tab2);

	mainController.addSubController(&baseSplit);

	MenuController popupMenu1;
	popupMenu1.setTitle("popupMenu1");
	popupMenu1.setIconPath("MenuTest.png");

	ActionController popuaction2;
	popuaction2.setTitle("Launch Sample");
	popuaction2.setIconPath("ActionTest2.png");
	popupMenu1.addSubController(&popuaction2);
	popupMenu1.popup();

	//Create script and assign it to sourceCode
	std::string testScriptPath = mydirectory;
	testScriptPath += "\\..\\..\\test.lua";

	LuaScript s;
	s.load(testScriptPath);

	ProxyList objs;
	objs.push_back(ProxyBase(&s));
	sourceCode.set(objs);

	//Run the application
	appController.run();
	
	//Load From Depot
	//if no applicationController found, 
}