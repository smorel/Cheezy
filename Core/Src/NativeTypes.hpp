
	typedef bool			Boolean;
	typedef unsigned int	Uint;
	typedef int				Integer;
	typedef	float			Float;
	typedef char			Byte;

	template<>
	class ParameterType<std::string>{
		typedef const std::string& Result;
	};
