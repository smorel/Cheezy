#pragma once

class SplitterController_Qt : public SplitterControllerImplementation{
	CLASS(SplitterController_Qt,SplitterControllerImplementation);
public:
	SplitterController_Qt();

	virtual void add(Controller* t, Integer i);
	virtual void remove(Controller* t, Integer i);

	virtual void* getView() const { return &spInnerData().splitter; }

protected:
	class InnerData{
	public:
		QSplitter splitter;
	};
	NoCopy<InnerData> spInnerData;
};