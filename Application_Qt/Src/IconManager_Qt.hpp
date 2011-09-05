class IconManager_Qt : public Singleton<IconManager_Qt>{
public:
	static const QIcon& getIcon(const std::string relativePath);
protected:
	typedef std::map<std::string, QIcon> IconMap;
	IconMap icons;
};