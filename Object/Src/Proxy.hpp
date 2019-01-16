class ProxyBase{
	CLASS(ProxyBase);
public:
	ProxyBase(const Descriptor* _acceptedType = 0);
	ProxyBase(Object* o, const std::string& p = "", const Descriptor* _acceptedType = 0);

	void set(AbstractObject v);
	AbstractObject get();

	void validate();
	Boolean isValid() const { return innerData().updated; }

	friend Boolean operator < (const ProxyBase& one,const ProxyBase& other);

protected:
	const ID& getReferenceId() const;
	void* getOwner() const;
	void _update();
	void _safeUpdate();
	void _attributeChanged();

protected:
	Boolean _accepted(const Descriptor* other);
	const Descriptor* acceptedType;
	Reference<Object> reference;
	std::string path;

	class InnerData{
	public:
		InnerData(){reset();}
		void reset(){
			attribute = 0;
			attributeOffset = 0;
			parentOffset = 0;
			updated = false;
		}

		const Attribute* attribute;
		INT_PTR attributeOffset;
		INT_PTR parentOffset;
		Boolean updated;
	};
	NoCopy<InnerData> innerData;
};

template<typename Type>
class Proxy : public ProxyBase{
	TEMPLATE_CLASS(ProxyBase,ProxyBase);
public:
	Proxy() 
		: ProxyBase(ReflectionManager::getInstance()->getDescriptor<Type>()){
	}

	Proxy(Object* o, const std::string& p)
		: ProxyBase(o,p,ReflectionManager::getInstance()->getDescriptor<Type>()){
	}

	void set(typename ParameterType<Type>::Result v){
		ProxyBase::set(AbstractObject(v));
	}

	typename ReturnType<Type>::Result get(){
		return *(ProxyBase::get().get<Type>());
	}

	TEMPLATE_CLASS_IMP(Proxy,Type);
	CLASS_END;
};

typedef std::vector<ProxyBase> ProxyList;

namespace Proxys{
	template<typename Type>
	void filter(const ProxyList& in,ProxyList& out){
		out.clear();
		for(ProxyList::size_type i = 0; i< in.size(); ++i){
			ProxyBase& p = const_cast<ProxyBase&>(in[i]);
			AbstractObject o = p.get();
			if(o.isKindOf<Type>()){
				out.push_back(p);
			}
		}
	}
}


class MethodProxyBase{
	CLASS(MethodProxyBase);
public:
	MethodProxyBase();
	MethodProxyBase(Object* o, const std::string& attribute, const std::string& method, const Descriptor* _acceptedType = 0);

	Boolean isCompatible(const MethodBase* m);
	void getSignature(std::vector<const Descriptor*>& retTypes,std::vector<const Descriptor*>& paramTypes);

	Boolean isValid();
	Boolean isAccessor();
	void execute(std::vector<Variant>& returnValues) ;
	void execute(const std::vector<AbstractObject>& paramValues) ;

	void validate();
protected:
	void _update();
	void _safeUpdate();
	void _attributeChanged();

	ProxyBase proxy;
	std::string methodId;

	class InnerData{
	public:
		InnerData() : method(0),updated(false){
		}
		const MethodBase* method;
		Boolean updated;
	};
	NoCopy<InnerData> innerData;
};