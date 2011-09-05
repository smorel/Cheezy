CLASS_IMP(FlowChartBlock);
CLASS_VALIDATE(&FlowChartBlock::validate);
	CLASS_ATTRIBUTECHANGED(&FlowChartBlock::_attributeChanged);
	ATTRIBUTE(object);
	ATTRIBUTE(x);
	ATTRIBUTE(y);
	ATTRIBUTE(outputParameterLinks);
	//ATTRIBUTE(outputLinks);
CLASS_END;

void FlowChartBlock::_attributeChanged(){
}

void FlowChartBlock::validate(){
}