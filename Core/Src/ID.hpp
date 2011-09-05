class ID{
	CLASS(ID);
public:
	ID();
	ID(const ID& other);
	ID(const std::string& str);

	static ID create();
	std::string toString() const;
	void fromString(const std::string& str);

	friend Boolean operator == (const ID& one,const ID& other);
	friend Boolean operator != (const ID& one,const ID& other);
	friend Boolean operator < (const ID& one,const ID& other);

	const ID& operator = (const ID& other);

	void serialize(void* data, const AbstractSerializer* s);

protected:
	UUID guid;
};