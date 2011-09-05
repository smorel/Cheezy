MAKE_TEST(FastDelegateUnitTest){
	class Test{
	public:
		Integer getValue(const std::string& s){
			Integer res = DefaultValue<Integer>::value;
			fromString<Integer>(s,res);
			return res;
		}
	};

	Test t;
	
    typedef FastDelegate1<const std::string&,Integer > MyDelegate;
	MyDelegate d(&t,&Test::getValue);
	Integer ret = d("5");
	//ASSERT(ret == 5);
};