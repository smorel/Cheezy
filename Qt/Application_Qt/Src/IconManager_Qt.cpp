
const QIcon& IconManager_Qt::getIcon(const std::string relativePath){
	std::string str = str::resolvePath(ApplicationGlobals::getInstance()->kIconPath + relativePath);
	IconMap::iterator itFound = getInstance()->icons.find(str);
	if(itFound != getInstance()->icons.end()){
		return itFound->second;
	}

	QIcon icon(str.c_str());
	getInstance()->icons[str] = icon;
	return getInstance()->icons[str];
}