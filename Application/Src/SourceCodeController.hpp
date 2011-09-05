
/*************************** SourceCodeController *************************
*/
class SourceCodeController;
class SourceCodeControllerImplementation;
typedef Implement<SourceCodeController,SourceCodeControllerImplementation,Controller> SourceCodeControllerBase;

class SourceCodeControllerImplementation : public SourceCodeControllerBase::Implementation
{
	CLASS(SourceCodeControllerImplementation);

protected:
	//already filtered ...
	virtual void set(LuaScript *s){};
	virtual void* getView()const{return 0;}

	friend SourceCodeController;
};

class SourceCodeController : public SourceCodeControllerBase
{
	CLASS(SourceCodeController,Controller);
public:
	void set(const ProxyList& selection);
	
	virtual void* getView()const;
};