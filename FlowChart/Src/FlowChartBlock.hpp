class FlowChartBlock : public Object{
	CLASS(FlowChartBlock,Object);
public:
	void validate();

protected:
	void _attributeChanged();

	Reference<Object> object;
	Integer x,y; //Change o Vector2<Int> when exists ...

	std::map<ProxyBase, std::vector<ProxyBase> > outputParameterLinks;
	//std::map<SignalProxyBase,std::vector<MethodProxyBase> > outputLinks;
};