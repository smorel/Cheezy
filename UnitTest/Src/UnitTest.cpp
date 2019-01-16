
	namespace {
		bool beginsWith(const std::string & source, const std::string & toSearch) {
			bool result = true;
			std::string::const_iterator sourceIt = source.begin();
			std::string::const_iterator toSearchIt = toSearch.begin();
			std::string::const_iterator sourceEnd = source.end();
			std::string::const_iterator toSearchEnd = toSearch.end();
			for(;result && sourceIt != sourceEnd && toSearchIt != toSearchEnd; ++sourceIt, ++toSearchIt) {
				result = *sourceIt == *toSearchIt;
			}
			return result || toSearchIt == toSearchEnd;
		}
	}

	void UnitTestManager::execute()
	{
		for(std::vector<UnitTest*>::iterator it(UnitTestManager::getInstance()->tests.begin()); 
			it != UnitTestManager::getInstance()->tests.end(); ++it) {
			UnitTest * pUnitTest = *it;
			//std::cout << "Running Test: " << pUnitTest->name << std::endl;
			pUnitTest->execute();
		}
	}

	void UnitTestManager::execute(const std::string & testString) {
		for(std::vector<UnitTest*>::iterator it(UnitTestManager::getInstance()->tests.begin()); 
			it != UnitTestManager::getInstance()->tests.end(); ++it) {
			UnitTest * pUnitTest = *it;
			if (beginsWith(pUnitTest->name, testString)) {
				pUnitTest->execute();
			}
		}
	}