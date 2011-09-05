
	template< typename T > class RemovePointer          { public: typedef T Result; };
	template< typename T > class RemovePointer<T*>      { public: typedef T Result; };
	template< typename T > class RemoveConst			{ public: typedef T Result; };
	template< typename T > class RemoveConst<const T>   { public: typedef T Result; };
	template< typename T > class RemoveRef				{ public: typedef T Result; };
	template< typename T > class RemoveRef<T&>			{ public: typedef T Result; };

	template< typename T > class ValueType	{ 
	public:
		typedef typename RemovePointer<T>::Result NoPointer;
		typedef typename RemoveConst<NoPointer>::Result NoPointerNoConst;
		typedef typename RemoveRef<NoPointerNoConst>::Result Result; 
	};

	template<typename T>
	class ParameterType{
	public:
		typedef typename ValueType<T>::Result vType;
		typedef const vType& Result;
	};

	template<typename T>
	class ReturnType{
	public:
		typedef typename ValueType<T>::Result vType;
		typedef const vType& Result;
	};

	template<typename T>
	class DefaultValue{
	public:
		static T value;
	};
	
	template<typename T>
	T DefaultValue<T>::value = 0;

	
	template<typename T>
	void fromString(const std::string& str, T& res){
		res = DefaultValue<T>::value;
	}

	template<typename T>
	void toString(const T& v, std::string& res){
		res = "None";
	}