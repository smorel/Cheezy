class Controller : public Object{
	CLASS(Controller,Object);
public:
	void setParent(Controller* c){innerData().parent = c;}
	Controller* getParent() const { return innerData().parent; }

	virtual void show(){};
	virtual void hovered(){};

	virtual void* getView()const{return 0;}

	/*
	virtual void mousePressEvent(QMouseEvent *);
    virtual void mouseReleaseEvent(QMouseEvent *);
    virtual void mouseDoubleClickEvent(QMouseEvent *);
    virtual void mouseMoveEvent(QMouseEvent *);
    virtual void wheelEvent(QWheelEvent *);
    virtual void keyPressEvent(QKeyEvent *);
    virtual void keyReleaseEvent(QKeyEvent *);
    virtual void focusInEvent(QFocusEvent *);
    virtual void focusOutEvent(QFocusEvent *);
    virtual void enterEvent(QEvent *);
    virtual void leaveEvent(QEvent *);
    virtual void paintEvent(QPaintEvent *);
    virtual void moveEvent(QMoveEvent *);
    virtual void resizeEvent(QResizeEvent *);
    virtual void closeEvent(QCloseEvent *);
    virtual void contextMenuEvent(QContextMenuEvent *);
    virtual void dragEnterEvent(QDragEnterEvent *);
    virtual void dragMoveEvent(QDragMoveEvent *);
    virtual void dragLeaveEvent(QDragLeaveEvent *);
    virtual void dropEvent(QDropEvent *);
    virtual void showEvent(QShowEvent *);
    virtual void hideEvent(QHideEvent *);
*/

protected:
	class InnerData{
	public:
		InnerData() : parent(0){}
		Controller* parent;
	};
	NoCopy<InnerData> innerData;
};

class ContainerController : public Controller{
	CLASS(ContainerController,Controller);
public:
	typedef Reference<Controller> SubController;
	typedef std::vector< SubController > SubControllers;

	void addSubController(const SubController& c, Integer i = -1);
	void removeSubController(Integer i);

	void validate();
	void showSubContainers();

protected:
	virtual void _onAddSubController(const SubController& c,Integer i){};
	virtual void _onRemoveSubController(const SubController& c){};

protected:
	SubControllers subControllers;
};

ENUM(EOrientation,
		eHorizontal,
		eVertical
	);

/*************************** SplitterController *************************
*/
class SplitterController;
class SplitterControllerImplementation;
typedef Implement<SplitterController,SplitterControllerImplementation,ContainerController> SplitterControllerBase;

class SplitterControllerImplementation : public SplitterControllerBase::Implementation
{
	CLASS(SplitterControllerImplementation);
protected:
	virtual void* getView() const{return 0;}
	virtual void add(Controller* c, Integer i){};
	virtual void remove(Controller* c){};
	friend class SplitterController;
};

class SplitterController : public SplitterControllerBase
{
	CLASS(SplitterController,Controller);
public:
	virtual void* getView() const;
protected:
	virtual void _onAddSubController(const SubController& c,Integer i){
		impInnerData().imp->add(c.get(),i);
	}
	virtual void _onRemoveSubController(const SubController& c){
		impInnerData().imp->remove(c.get());
	}
protected:
	EOrientation orientation;
};


/*************************** TabController *************************
*/
class TabController;
class TabControllerImplementation;
typedef Implement<TabController,TabControllerImplementation,ContainerController> TabControllerBase;

class TabControllerImplementation : public TabControllerBase::Implementation
{
	CLASS(TabControllerImplementation);
protected:
	virtual void* getView() const {return 0;}
	virtual void add(Controller* c, Integer i){};
	virtual void remove(Controller* c){};
	friend class TabController;
};

class TabController : public TabControllerBase
{
	CLASS(TabController,Controller);
public:
	virtual void* getView() const;
protected:
	virtual void _onAddSubController(const SubController& c,Integer i){
		impInnerData().imp->add(c.get(),i);
	}
	virtual void _onRemoveSubController(const SubController& c){
		impInnerData().imp->remove(c.get());
	}
protected:
	EOrientation orientation;
};


template<typename ReturnType>
ReturnType* getParentView(Controller* in){
	Controller* c = in ? in->getParent() : 0;
	while(c != 0){
		void* v = c->getView();
		if(v)
			return static_cast<ReturnType*>(v);
		c = c->getParent();
	}
	return 0;
}