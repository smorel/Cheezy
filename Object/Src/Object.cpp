CLASS_IMP(Object);
	ATTRIBUTE(id);
CLASS_END;

CLASS_IMP(PlaceHolder);
CLASS_END;


Object* Object::replace(Object* o, Object* by){
	return by;
}