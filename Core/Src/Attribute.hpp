
	class AttributeExtension;
	class AccessorBase;
	class MutatorBase;
	class Attribute{
	public:
		Attribute(const std::string& _name,Uint _offset,
			const Descriptor* _descriptor,const Descriptor* _containerDescriptor);
		~Attribute();

		const std::string& getName() const { return name;}
		const unsigned int getOffset() const { return offset; }
		const Descriptor* getDescriptor() const { return descriptor; }
		const Descriptor* getContainerDescriptor() const { return containerDescriptor; }

		AbstractObject get(void* owner) const;
		void set(void* owner, AbstractObject o) const;

		void add(void* owner,const AbstractObject& key, const AbstractObject& value) const;
		void remove(void* owner, const AbstractObject& key) const;

	protected:
		const std::string name;
		const Uint offset;
		const Descriptor* descriptor;
		const Descriptor* containerDescriptor;

	public:
		AttributeExtension* extension;
	};
