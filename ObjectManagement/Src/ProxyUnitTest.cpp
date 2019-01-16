namespace ProxyUnitTest_CPP{
	class Dummy : public Object{
		CLASS(Dummy,Object);
	public:
		class Inner{
		CLASS(Inner);
		public:
			Inner() : o(5){}
			void callMe(){
			}

			Uint o;
		};

		Dummy() : u(0){
		}

		void set(Uint _u){
			u = _u;
		}

		Uint get() const {
			return u;
		}

	protected:
		Uint u;
		Inner i;
	};

	
}

	CLASS_IMP(ProxyUnitTest_CPP::Dummy);
		ATTRIBUTE_GETSET(u,&Dummy::get,&Dummy::set);
		ATTRIBUTE(i);
	CLASS_END;

	CLASS_IMP(ProxyUnitTest_CPP::Dummy::Inner);
		ATTRIBUTE(o);
		FUNCTION(&ProxyUnitTest_CPP::Dummy::Inner::callMe);
	CLASS_END;

MAKE_TEST(ProxyUnitTest)
{
	ObjectContextCoordinator::registerObjectContext(
		"ProxyUnitTest",new ObjectContext());
	ProxyUnitTest_CPP::Dummy* t = 
		ObjectContextCoordinator::allocate<ProxyUnitTest_CPP::Dummy>("ProxyUnitTest");
	Proxy<Uint> testProxy(t,"i/o");
	Uint g = testProxy.get();
	testProxy.set(8);
	Uint g2 = testProxy.get();

	Uint u = 5;
	Variant v(u);
	Uint uRet = *v.get<Uint>();

	Variant v2(*t);

	MethodProxyBase m(t,"i","callMe");
	std::vector<AbstractObject> params;
	m.execute(params);
}