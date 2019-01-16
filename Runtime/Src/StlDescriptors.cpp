
	STL_CLASS_IMP(string);


	//Unit Tests
	namespace StlDescriptorsUnitTest_CPP{
		class Dummy{
			CLASS(Dummy);
		protected:
			std::vector<Uint> v;
		};

	}
	CLASS_IMP(StlDescriptorsUnitTest_CPP::Dummy);
		ATTRIBUTE(v);
	CLASS_END;

	MAKE_TEST(StlDescriptorsUnitTest)
	{
		StlDescriptorsUnitTest_CPP::Dummy d;
	}