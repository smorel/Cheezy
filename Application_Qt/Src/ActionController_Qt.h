#pragma once

class ActionController_Qt;
class Action_Qt : public QAction{
	Q_OBJECT;
public:
	Action_Qt();
	void initialize(ActionController_Qt * c);

protected slots:
	void _hovered();
	void _triggered( bool checked );

protected:
	ActionController_Qt* controller;
};

class ActionController_Qt : public ActionControllerImplementation{
	CLASS(ActionController_Qt,ActionControllerImplementation);
public:
	ActionController_Qt();
	Action_Qt* getAction() const { return &actionInnerData().action; }

protected:
	virtual void update();

protected:
	class InnerData{
	public:
		Action_Qt action;
	};
	NoCopy<InnerData> actionInnerData;
	friend class Action_Qt;
};
