CLASS_IMP(SourceCodeController_Qt);
	IMPLEMENTATION_OVERLOAD(kQtImplementation,SourceCodeControllerImplementation);
CLASS_END;

SourceCodeController_Qt::SourceCodeController_Qt(){
}

void SourceCodeController_Qt::set(LuaScript *s){
	scInnerData().currentScript = s;
	if(s){
		scInnerData().m_editControl.editor()->setText(s->getData().c_str());
	}
}


SourceCodeController_Qt::InnerData::InnerData()
: m_session("session"),m_languages(&m_formats),currentScript(0){
	std::string scriptDefPath = ApplicationGlobals::getInstance()->kWorkingPath;
	scriptDefPath += "..\\..\\ScriptLanguageDefinition\\";
	scriptDefPath = str::resolvePath(scriptDefPath);

	std::string luaDef = scriptDefPath + "lua.qxf";
	m_formats.load(luaDef.c_str());
	QDocument::setDefaultFormatScheme(&m_formats);

	std::string marksDef = scriptDefPath + "marks.qxm";
	QLineMarksInfoCenter::instance()->loadMarkTypes(marksDef.c_str());

	m_session.addEditor(m_editControl.editor());
	
	//m_editControl.editor()->setInputBinding(m_snippetBinding);
	m_editControl.addPanel("Line Mark Panel", QCodeEdit::West, true)->setShortcut(QKeySequence("F6"));
	m_editControl.addPanel("Line Number Panel", QCodeEdit::West, true)->setShortcut(QKeySequence("F11"));
	m_editControl.addPanel("Fold Panel", QCodeEdit::West, true)->setShortcut(QKeySequence("F9"));
	m_editControl.addPanel("Line Change Panel", QCodeEdit::West, true);
	m_editControl.addPanel("Status Panel", QCodeEdit::South, true);
	m_editControl.addPanel("Goto Line Panel", QCodeEdit::South);
	m_editControl.addPanel("Search Replace Panel", QCodeEdit::South);
	
	m_languages.addDefinitionPath(scriptDefPath.c_str());
	m_languages.setLanguage(m_editControl.editor(), "dummy.lua");
}