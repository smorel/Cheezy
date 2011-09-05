namespace str{
	int split(const std::string& s, const std::string& separator,std::vector<std::string>& L, 
		bool keeptoken = false, bool noWhiteSpace = false );

	inline std::string trim_right(const std::string &source , const std::string& t = " "){
		std::string str = source;
		return str.erase( str.find_last_not_of(t) + 1);
	}

	inline std::string trim_left( const std::string& source, const std::string& t = " "){
		std::string str = source;
		return str.erase(0 , source.find_first_not_of(t) );
	}

	inline std::string trim(const std::string& source, const std::string& t = " "){
		std::string str = source;
		return trim_left( trim_right( str , t) , t );
	} 

	std::string replace(const std::string& in, const std::string& rep, const std::string& by);

	std::string resolvePath(const std::string& path);
}