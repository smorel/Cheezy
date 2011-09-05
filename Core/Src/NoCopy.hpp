
	template<typename Type>
	class NoCopy{
	public:
		NoCopy(){}
		NoCopy(const NoCopy& other){}
		const NoCopy& operator= (const NoCopy& other){return *this;}

		Type& operator()() const {return instance;}
	private:
		mutable Type instance;
	};
