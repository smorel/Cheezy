
	class DescriptorExtension;
	template<typename Type, typename ParentDescriptor = Descriptor>
	class TypedDescriptor : public ParentDescriptor{
	public:
		TypedDescriptor(const std::string& _name, const Uint _size, const Descriptor* _parentDescriptor,
			DescriptorExtension* ext, const std::string& subTypes)
			: ParentDescriptor(_name,_size,_parentDescriptor,ext,subTypes){
		}

		virtual void* allocate() const{
			return MemoryManager::getInstance()->allocate<Type>(extension->getMemoryCategory());
		}

		virtual void deallocate(void* memory) const{
			MemoryManager::getInstance()->deallocate<Type>(memory,extension->getMemoryCategory());
		}

		virtual void copy(void* source, void* target) const{
			Type* s = reinterpret_cast<Type*>(source);
			Type* t = reinterpret_cast<Type*>(target);
			//Pass through copy constructor
			*t = Type(*s);
		}
	};
