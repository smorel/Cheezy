class Object{
	CLASS(Object);
	friend class ObjectContext;
public:
	const ID& getId() const { return id; }

	void setName(const std::string& s){ name = s; }
	const std::string& getName() const { return name; }

	template<typename Type>
	Boolean isKindOf(){
		return getDescriptor()->isKindOf<Type>();
	}

	static Object* replace(Object* o, Object* by);
	static Object* fetchObject(const ID& id);

protected:
	std::string name;

private:
	//Attention a ID il ne faudra pas le dupliquer lors du copy/paste ...
	ID id;
};

class PlaceHolder : public Object{
	CLASS(PlaceHolder,Object);
	friend class ObjectContext;

public:
	PlaceHolder() : type(0){
	}

	const Descriptor* getType() const{return type;}

protected:
	const Descriptor* type;
};
