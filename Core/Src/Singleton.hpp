	
	template<typename Type>
	class Singleton{
	public:
		Singleton(){
			if(!instance){
				instance = (Type*)this;
			}
		}

		~Singleton(){
		}

		static Type* getInstance() { if(!instance) instance = new Type(); return instance; }

	protected:
		static Type* instance;
	};

	
	template<typename Type>
	Type* Singleton<Type>::instance = 0;
