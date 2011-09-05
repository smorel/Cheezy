//IMPLEMENTER AVEC LA LIB SIGNALSLOT
//ET VIRER SIGNALSLOT.HPP DE CORE




class SignalConcept{
	CLASS(SignalConcept);
};

/*
class AbstractSignalProxy{
	CLASS(AbstractSignalProxy);
public:
	cSignal<bool, const Variant&, const std::vector<AbstractObject>& > proxySignal;
};


template <typename tRet, typename tArg1,
                      typename tArg2,
                      typename tArg3,
                      typename tArg4,
                      typename tArg5>
class AbstractSignalProxyFactory{
public:
	class Proxy : public AbstractSignalProxy{
		TEMPLATE_CLASS(Proxy,AbstractSignalProxy);
	public:
		Proxy(){
			proxySlot.AssignFunction(this,&Proxy::proxyFunction);
		}
	public:
		tRet proxyFunction(tArg1 a1,tArg2 a2,tArg3 a3,tArg4 a4,tArg5 a5){
			const Descriptor* d = ReflectionManager::getDescriptor<typename tRet>();
			Variant returnValue(0,d);

			std::vector<Variant> ret;
			ret.push_back(AbstractObject(returnValue.getAdress(),d));

			std::vector<AbstractObject> params;
			if(ReflectionManager::getDescriptor(&a1) != 0)
				params.push_back(AbstractObject(a1));
			if(ReflectionManager::getDescriptor(&a2) != 0)
				params.push_back(AbstractObject(a2));
			if(ReflectionManager::getDescriptor(&a3) != 0)
				params.push_back(AbstractObject(a3));
			if(ReflectionManager::getDescriptor(&a4) != 0)
				params.push_back(AbstractObject(a4));
			if(ReflectionManager::getDescriptor(&a5) != 0)
				params.push_back(AbstractObject(a5));
			proxySignal.Fire(returnValue,params);

			return *(returnValue.get<typename tRet>());
		}

	public:
		cSlot<Proxy,
			typename tRet,
			typename tArg1,
			typename tArg2,
			typename tArg3,
			typename tArg4,
			typename tArg5> proxySlot;
		friend class AbstractSignalProxyFactory;

		TEMPLATE_CLASS_IMP(Proxy,tRet,tArg1,tArg2,tArg3,tArg4,tArg5);
			ATTRIBUTE(proxySlot);
		CLASS_END;
	};

	static AbstractSignalProxy* create(void* target){
		Proxy* p = MemoryManager::getInstance()->allocate<Proxy>("SignalProxy");
		cSignal<tRet,tArg1,tArg2,tArg3,tArg4,tArg5>& s = *(reinterpret_cast< 
			cSignal<tRet,tArg1,tArg2,tArg3,tArg4,tArg5>* >(target));
		s.Connect(p->proxySlot);
		return p;
	};
};
*/

class SignalDescriptorBase : public Descriptor{
public:
	SignalDescriptorBase(const std::string& _name, const Uint _size, const Descriptor* _parentDescriptor,
			DescriptorExtension* ext, const std::string& subTypes)
			: Descriptor(_name,_size,_parentDescriptor,ext,subTypes){
				setConcept(ReflectionManager::getDescriptor<SignalConcept>());
		}
/*
	virtual AbstractSignalProxy* createProxy(void* target) const{
		return 0;
	}
	*/
};

template <class tRet, class tArg1=NoType,
                      class tArg2=NoType,
                      class tArg3=NoType,
                      class tArg4=NoType,
                      class tArg5=NoType>
class SignalDescriptor : public TypedDescriptor< cSignal<tRet,tArg1,tArg2,tArg3,tArg4,tArg5>,SignalDescriptorBase >{
public:
	SignalDescriptor(const std::string& _name, const Uint _size, const Descriptor* _parentDescriptor,
			DescriptorExtension* ext, const std::string& subTypes)
			: TypedDescriptor(_name,_size,_parentDescriptor,ext,subTypes){
				setConcept(ReflectionManager::getDescriptor<SignalConcept>());
		}
/*
	virtual AbstractSignalProxy* createProxy(void* target) const{
		return AbstractSignalProxyFactory<tRet,tArg1,tArg2,tArg3,tArg4,tArg5>::create(target);
	}
	*/
};

template <class tRet, class tArg1=NoType,
                      class tArg2=NoType,
                      class tArg3=NoType,
                      class tArg4=NoType,
                      class tArg5=NoType>
class SignalDescriptorRetriever{
protected:
	static void _buildDescriptor(){
		if(!descriptor){
			DescriptorExtension* ext = new DescriptorExtension();
			descriptor = 
				new SignalDescriptor< tRet,tArg1,tArg2,tArg3,tArg4,tArg5 >(
					"Signal",sizeof(cSignal<tRet,tArg1,tArg2,tArg3,tArg4,tArg5>),0,ext,
					TypeNameConcatenator<tRet,tArg1,tArg2,tArg3,tArg4,tArg5>::get());
			//ext->registerSerialize("serialize",&StlDescriptor< InterestType >::serialize);
			ReflectionManager::getInstance()->registerDescriptor(descriptor);
		}
	}
	static Descriptor* descriptor;
};

template <class tRet, class tArg1,class tArg2,class tArg3, class tArg4,class tArg5>
Descriptor* SignalDescriptorRetriever< tRet,tArg1,tArg2,tArg3,tArg4,tArg5 >::descriptor = 0;

#define SIGNAL_DESCRIPTOR_DEF(...)\
	class DescriptorRetriever< cSignal<__VA_ARGS__> >\
		: public SignalDescriptorRetriever<__VA_ARGS__> {\
	public:\
		static const Descriptor* getDescriptor(){\
			_buildDescriptor();\
			return descriptor;\
		}\
		typedef cSignal<__VA_ARGS__> InterestType;\
		static const Descriptor* getDescriptor(InterestType* o){\
			_buildDescriptor();\
			return descriptor;\
		}\
	}

template <class tRet>
SIGNAL_DESCRIPTOR_DEF(tRet);

template <class tRet, class tArg1>
SIGNAL_DESCRIPTOR_DEF(tRet,tArg1);

template <class tRet, class tArg1,class tArg2>
SIGNAL_DESCRIPTOR_DEF(tRet,tArg1,tArg2);

template <class tRet, class tArg1,class tArg2, class tArg3>
SIGNAL_DESCRIPTOR_DEF(tRet,tArg1,tArg2,tArg3);

template <class tRet, class tArg1,class tArg2, class tArg3, class tArg4>
SIGNAL_DESCRIPTOR_DEF(tRet,tArg1,tArg2,tArg3,tArg4);

template <class tRet, class tArg1,class tArg2, class tArg3, class tArg4, class tArg5>
SIGNAL_DESCRIPTOR_DEF(tRet,tArg1,tArg2,tArg3,tArg4,tArg5);



class SlotConcept{
	CLASS(SlotConcept);
};

class SlotDescriptorBase : public Descriptor{
public:
	SlotDescriptorBase(const std::string& _name, const Uint _size, const Descriptor* _parentDescriptor,
			DescriptorExtension* ext, const std::string& subTypes)
			: Descriptor(_name,_size,_parentDescriptor,ext,subTypes){
				setConcept(ReflectionManager::getDescriptor<SlotConcept>());
		}
};

template <class cInstance, class tRet, class tArg1=NoType,
                      class tArg2=NoType,
                      class tArg3=NoType,
                      class tArg4=NoType,
                      class tArg5=NoType>
class SlotDescriptor : public TypedDescriptor< cSlot<cInstance,tRet,tArg1,tArg2,tArg3,tArg4,tArg5>, SlotDescriptorBase >{
public:
	SlotDescriptor(const std::string& _name, const Uint _size, const Descriptor* _parentDescriptor,
			DescriptorExtension* ext, const std::string& subTypes)
			: TypedDescriptor(_name,_size,_parentDescriptor,ext,subTypes){
		}
};

template <class cInstance, class tRet, class tArg1=NoType,
                      class tArg2=NoType,
                      class tArg3=NoType,
                      class tArg4=NoType,
                      class tArg5=NoType>
class SlotDescriptorRetriever{
protected:
	static void _buildDescriptor(){
		if(!descriptor){
			DescriptorExtension* ext = new DescriptorExtension();
			descriptor = 
				new SlotDescriptor< cInstance,tRet,tArg1,tArg2,tArg3,tArg4,tArg5 >(
					"Slot",sizeof(cSlot<cInstance,tRet,tArg1,tArg2,tArg3,tArg4,tArg5>),0,ext,
					TypeNameConcatenator<cInstance,tRet,tArg1,tArg2,tArg3,tArg4,tArg5>::get());
			//ext->registerSerialize("serialize",&StlDescriptor< InterestType >::serialize);
			ReflectionManager::getInstance()->registerDescriptor(descriptor);
		}
	}
	static Descriptor* descriptor;
};

template <class cInstance,class tRet, class tArg1,class tArg2,class tArg3, class tArg4,class tArg5>
Descriptor* SlotDescriptorRetriever<cInstance,tRet,tArg1,tArg2,tArg3,tArg4,tArg5>::descriptor = 0;


#define SLOT_DESCRIPTOR_DEF(...)\
	class DescriptorRetriever< cSlot<__VA_ARGS__> >\
		: public SlotDescriptorRetriever<__VA_ARGS__> {\
	public:\
		static const Descriptor* getDescriptor(){\
			_buildDescriptor();\
			return descriptor;\
		}\
		typedef cSlot<__VA_ARGS__> InterestType;\
		static const Descriptor* getDescriptor(InterestType* o){\
			_buildDescriptor();\
			return descriptor;\
		}\
	}

template <class cInstance, class tRet>
SLOT_DESCRIPTOR_DEF(cInstance,tRet);

template <class cInstance, class tRet, class tArg1>
SLOT_DESCRIPTOR_DEF(cInstance,tRet,tArg1);

template <class cInstance, class tRet, class tArg1,class tArg2>
SLOT_DESCRIPTOR_DEF(cInstance,tRet,tArg1,tArg2);

template <class cInstance, class tRet, class tArg1,class tArg2, class tArg3>
SLOT_DESCRIPTOR_DEF(cInstance,tRet,tArg1,tArg2,tArg3);

template <class cInstance, class tRet, class tArg1,class tArg2, class tArg3, class tArg4>
SLOT_DESCRIPTOR_DEF(cInstance,tRet,tArg1,tArg2,tArg3,tArg4);

template <class cInstance, class tRet, class tArg1,class tArg2, class tArg3, class tArg4, class tArg5>
SLOT_DESCRIPTOR_DEF(cInstance,tRet,tArg1,tArg2,tArg3,tArg4,tArg5);