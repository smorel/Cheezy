io.write("Script begin");
object1 = MacroDefinitionValidation();
io.write("object1 created");
-- here object1 is nil : trying to understand why
local res = object1:getThing();
io.write("object1 getThing called");
object1.u = 48;
io.write("object1 property u set called");
object1.f = 1.3;
io.write("object1 property f set called");
local t = object1.f;

object2 = SourceCodeController();
object3 = SplitterController();
object4 = TabController();

io.write("test threads and sleep functionality ...");
--while 1 do
--	thread.sleep(1);
--end