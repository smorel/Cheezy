//IMPLEMENTER AVEC LA LIB SIGNALSLOT
//ET VIRER SIGNALSLOT.HPP DE CORE

namespace SignalSlotUnitTest_cpp{
	class Test{
		CLASS(Test);
	public:
		cSignal<Uint, const std::string&> signal;
	};

	class TestReceiver{
		CLASS(TestReceiver);
	public:
		TestReceiver(){
			slot.AssignFunction(this, &TestReceiver::onSignal, "TestReceiver::onSignal");
		}
		cSlot<TestReceiver, Uint, const std::string&> slot;
		
	private:
		Uint onSignal(const std::string& str){
			Uint i;
			fromString(str,i);
			return i;
		}
	};

	class TestProxyReceiver{
		CLASS(TestProxyReceiver);
	public:
		TestProxyReceiver(){
			slot.AssignFunction(this, &TestProxyReceiver::onSignal, "TestProxyReceiver::onSignal");
		}
		cSlot<TestProxyReceiver, bool,std::vector<Variant>&,std::vector<AbstractObject>&> slot;
		
	private:
		bool onSignal(std::vector<Variant>& ret,std::vector<AbstractObject>& params){
			return 0;
		}
	};
}

CLASS_IMP(SignalSlotUnitTest_cpp::Test);
	ATTRIBUTE(signal);
CLASS_END;

CLASS_IMP(SignalSlotUnitTest_cpp::TestReceiver);
	ATTRIBUTE(slot);
CLASS_END;

CLASS_IMP(SignalSlotUnitTest_cpp::TestProxyReceiver);
CLASS_END;

MAKE_TEST(SignalSlotUnitTest){
	SignalSlotUnitTest_cpp::Test t;
	SignalSlotUnitTest_cpp::TestReceiver tr;
    t.signal.Connect(tr.slot);
	Uint res = t.signal.Fire("5");
	//ASSERT(res == 5);

	const Descriptor* d = ReflectionManager::getDescriptor<SignalSlotUnitTest_cpp::Test>();
	if(d->isConcept<SignalConcept>()){
		const SignalDescriptorBase* sd = static_cast< const SignalDescriptorBase*>(d);
		/*AbstractSignalProxy* p = sd->createProxy(&t.signal);

		SignalSlotUnitTest_cpp::TestProxyReceiver tr;
		p->proxySignal.Connect(tr.slot);
		*/
	}
};