#pragma once

class SourceCodeController_Qt : public SourceCodeControllerImplementation{
	CLASS(SourceCodeController_Qt,SourceCodeControllerImplementation);
public:
	SourceCodeController_Qt();

	virtual QWidget* getWidget() const { return 0; }
	virtual void* getView() const { return scInnerData().m_editControl.editor(); }

protected:
	virtual void set(LuaScript *s);

	class InnerData{
	public:
		InnerData();

		QEditSession	m_session;
		QCodeEdit		m_editControl;
		QFormatScheme	m_formats;
		QLanguageFactory m_languages;

		LuaScript* currentScript;
	};
	NoCopy<InnerData> scInnerData;
};