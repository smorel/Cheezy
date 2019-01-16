
	class Attribute;
	class MethodBase;
	class DescriptorExtension;
	class AbstractScriptLanguage;

	class Descriptor{
	public:
		typedef std::vector<const MethodBase*> OrderedMethods;
		typedef std::map<const std::string,const MethodBase*> Methods;
		typedef std::vector<const Attribute*> OrderedAttributes;
		typedef std::map<const std::string,const Attribute*> Attributes;

		Descriptor(const std::string& _name, const Uint _size, const Descriptor* _parentDescriptor,
			DescriptorExtension* ext, const std::string& subTypes);
		~Descriptor();

		const std::string& getName() const { return name;}

		void registerAttibute(const Attribute* attribute);
		const Attribute* getAttribute(const std::string& attributeName) const;
		const OrderedAttributes& getAttributes() const {return orderedAttributes;}

		void registerMethod(const MethodBase* m);
		const MethodBase* getMethod(const std::string& name) const;
		const OrderedMethods& getMethods() const {return orderedMethods;}

		Boolean isKindOf(const Descriptor* d) const;

		template<typename Type>
		Boolean isKindOf() const{
			return isKindOf(ReflectionManager::getDescriptor<Type>());
		}

		const Descriptor* getParentDescriptor() const { return parentDescriptor; }
		const Descriptor* getConcept() const { return concept; }
		void setConcept(const Descriptor* d){concept = d; }

		template<typename Type>
		Boolean isConcept() const{
			return concept == ReflectionManager::getDescriptor<Type>();
		}

		Uint getSize() const { return size; }

		//Overridable
	public:
		virtual void* allocate() const;
		virtual void deallocate(void* memory) const;
		virtual void copy(void* source, void* target) const;
		
	protected:
		std::string name;
		const Descriptor* parentDescriptor;
		const Descriptor* concept;
		const Uint size;

		OrderedAttributes orderedAttributes;
		Attributes attributes;
		
		OrderedMethods orderedMethods;
		Methods methods;

	public:
		DescriptorExtension* extension;
	};

	
	template<typename Type>
	class DescriptorRetriever{
	public:
		static const Descriptor* getDescriptor(){
			return Type::getClassDescriptor();
		}

		static const Descriptor* getDescriptor(Type* o){
			return o->getDescriptor();
		}
	};
