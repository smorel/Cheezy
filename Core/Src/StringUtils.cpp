namespace str{
	int split(const std::string& s, const std::string& separator,std::vector<std::string>& L, 
		bool keeptoken, bool noWhiteSpace )
	{
		typedef std::string::size_type ST;
		std::string delims = separator;
		std::string STR;
		if(delims.empty()) delims = "\n\r";
		if(noWhiteSpace) delims += " ";
		ST pos=0, LEN = s.size();
		while(pos < LEN ){
			STR=""; // Init/clear the STR token buffer
			// remove any delimiters including optional (white)spaces
			while( (delims.find(s[pos]) != std::string::npos) && (pos < LEN) ) ++pos;
			// leave if @eos
			if(pos==LEN) return L.size();
			// Save token data
			while( (delims.find(s[pos]) == std::string::npos) && (pos < LEN) ) STR += s[pos++];
			// put valid STR buffer into the supplied list
			//std::cout << "[" << STR << "]";
			if( ! STR.empty() ) L.push_back(STR);
		}
		return L.size();
	}

	
	std::string replace(const std::string& in, const std::string& rep, const std::string& by){
		std::string ret = in;
		std::string::size_type it = ret.find(rep);
		while(it < ret.size()){
			ret.replace(it,rep.length(),by);
			it = ret.find(rep,it+by.length());
		}
		return ret;
	}
	
	std::string resolvePath(const std::string& path){
		std::string tmp = str::replace(path,"\\","/");

		std::vector<std::string> splitted;
		str::split(tmp,"/",splitted);

		std::string res;
		Integer toSkip = 0;
		for(Integer i = (Integer)(splitted.size() - 1); i >= 0; --i){
			std::string& s = splitted[i];
			if(s == "..") ++toSkip;
			else if(s != "."){
				if(toSkip == 0){
					if(i == splitted.size() - 1){
						std::string::size_type itPoint = s.find(".");
						if(itPoint >=0 && itPoint < s.length())
							res.insert(0,s);
						else{
							res.insert(0,s + "/");
						}
					}
					else{
						res.insert(0,s + "/");
					}
				}else{
					--toSkip;
				}
			}
		}
		return res;
	}
}