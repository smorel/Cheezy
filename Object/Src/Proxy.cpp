CLASS_IMP(ProxyBase);
	CLASS_VALIDATE(&ProxyBase::validate);
	CLASS_ATTRIBUTECHANGED(&ProxyBase::_attributeChanged);
	ATTRIBUTE(reference);
	ATTRIBUTE(path);
CLASS_END;

ProxyBase::ProxyBase(const Descriptor* _acceptedType)
	: acceptedType(_acceptedType){
}

ProxyBase::ProxyBase(Object* o, const std::string& p,const Descriptor* _acceptedType)
	: reference(o),path(p),acceptedType(_acceptedType){
	_update();
}

void ProxyBase::validate(){
	_update();
}

void ProxyBase::_update(){
	innerData().reset();

	const Descriptor* d = reference ? reference->getDescriptor() : 0;
	if(!d || reference.isNull())
		return;

	if(path.empty() && reference){//Direct Object
		innerData().updated = true;
		return;
	}

	//Attribute
	std::vector<std::string> atts;
	str::split(path, "/" ,atts);

	for(std::vector<std::string>::size_type i=0;i<atts.size();++i){
		std::string& attName = atts[i];
		const Attribute* a = d->getAttribute(attName);
		if(!a){
			break;
		}

		if(i < atts.size() - 1){
			innerData().parentOffset += a->getOffset();
		}
		else{
			innerData().attribute = a;
			innerData().attributeOffset = innerData().parentOffset + a->getOffset();
		}

		d = a->getDescriptor();
		innerData().updated = true;
	}

	if(innerData().attribute && !_accepted(innerData().attribute->getDescriptor())){
		innerData().reset();
	}
}

void ProxyBase::_safeUpdate(){
	if(!innerData().updated){
		_update();
	}
}

Boolean ProxyBase::_accepted(const Descriptor* other){
	return acceptedType == 0 || other->isKindOf(acceptedType);
}

void ProxyBase::set(AbstractObject v){
	_safeUpdate();
	if(innerData().attribute){//Attribute
		innerData().attribute->set(getOwner(),v);
	}
	else if(reference){//Direct Object
		const Descriptor* d = reference->getDescriptor();
		//Assert d == v.getDescriptor()
		d->copy(v.getAdress(),reference.get());
	}
}

AbstractObject ProxyBase::get(){
	_safeUpdate();
	if(innerData().attribute){//Attribute
		return innerData().attribute->get(getOwner());
	}else if(reference){//Direct Object
		return AbstractObject(reference.get(),
			reference.get()->getDescriptor());
	}
	return AbstractObject();
}

void* ProxyBase::getOwner() const{
	if(reference){
		return (void*)((INT_PTR)reference.get() + innerData().parentOffset);
	}
	return 0;
}

void ProxyBase::_attributeChanged(){
	_update();
}

const ID& ProxyBase::getReferenceId() const{
	if(reference.get()){
		return reference.get()->getId();
	}
	static ID defaultId;
	return defaultId;
}

Boolean operator < (const ProxyBase& one,const ProxyBase& other){
	return one.getReferenceId() < other.getReferenceId()
		&& one.path < other.path;
}

CLASS_IMP(MethodProxyBase);
	CLASS_VALIDATE(&MethodProxyBase::validate);
	CLASS_ATTRIBUTECHANGED(&MethodProxyBase::_attributeChanged);
	ATTRIBUTE(proxy);
	ATTRIBUTE(methodId);
CLASS_END;

MethodProxyBase::MethodProxyBase(){
}

MethodProxyBase::MethodProxyBase(Object* o, const std::string& attribute, const std::string& method, const Descriptor* _acceptedType)
: proxy(o,attribute,_acceptedType),methodId(method){
}

void MethodProxyBase::getSignature(std::vector<const Descriptor*>& retTypes,std::vector<const Descriptor*>& paramTypes){
	if(innerData().method){
		retTypes = innerData().method->getReturnTypes();
		paramTypes =  innerData().method->getAttributeTypes();
	}
}

Boolean MethodProxyBase::isCompatible(const MethodBase* m){
	_safeUpdate();
	if(innerData().method){
		return innerData().method->getReturnTypes() == m->getReturnTypes()
			&& innerData().method->getAttributeTypes() == m->getAttributeTypes();
	}
	return false;
}

Boolean MethodProxyBase::isValid(){
	_safeUpdate();
	return proxy.isValid() && innerData().method != 0;
}

Boolean MethodProxyBase::isAccessor(){
	_safeUpdate();
	return innerData().method && innerData().method->getMethodType() == MethodBase::eGetter;;
}

void MethodProxyBase::execute(std::vector<Variant>& returnValues) {
	if(isValid() && isAccessor()){
		const GetterBase* a = static_cast<const GetterBase*>(innerData().method);
		a->execute(proxy.get().getAdress(),returnValues);
	}
}

void MethodProxyBase::execute(const std::vector<AbstractObject>& paramValues) {
	if(isValid() && !isAccessor()){
		const SetterBase* a = static_cast<const SetterBase*>(innerData().method);
		a->execute(proxy.get().getAdress(),paramValues);
	}
}

void MethodProxyBase::validate(){
	_update();
}

void MethodProxyBase::_update(){
	innerData().updated = false;
	const Descriptor* d = proxy.get().getDescriptor();
	if(d){
		innerData().method = d->getMethod(methodId);
		innerData().updated = (innerData().method != 0);
	}
}

void MethodProxyBase::_safeUpdate(){
	if(!innerData().updated){
		_update();
	}
}

void MethodProxyBase::_attributeChanged(){
	_update();
}