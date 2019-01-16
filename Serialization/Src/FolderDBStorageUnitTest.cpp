

/* UNIT TEST
*/

	class MacroDefinitionValidation : public Object{
		CLASS(MacroDefinitionValidation,Object);
	public:
		MacroDefinitionValidation(){
		}

		class Toto{
			CLASS(Toto);
			/*void serialize(void* data, const ISerializer* s){
				s.serialize(u,"u");
			}*/
		public:
			Uint u;

			class Test : public Object{
				CLASS(Test,Object);
			public:
				Proxy<Uint> proxy;
			};

			Reference<Test> t;
		};

		void delegateTest(){};

	protected:
		Uint getThing() const{return 1;}
		/*void getThing1(Uint& u1) const{}
		void getThing2(Uint& u1,Float& u2) const{}
		void getThing3(Uint& u1,Float& u2,Boolean& u3) const{}
		void getThing4(Uint& u1,Float& u2,Boolean& u3,Toto& u4) const{}*/
		void setThing1(const Toto& t){}
		void validate(){}
		void func0(){}

		void migration(const MigrationData* d){}

		Float getF() const { return 5; }
		void setF(Float _f) { f = _f; }

	public:
		Boolean bo;
		Float f;
		Uint u;
		Integer i;
		Toto t;
		std::vector<Uint> v;
	};

	CLASS_IMP(MacroDefinitionValidation::Toto::Test);
		ATTRIBUTE(proxy);
	CLASS_END;
	
	CLASS_IMP(MacroDefinitionValidation::Toto);
		CLASS_MEMORY_CATEGORY("MyCategory");
		//CLASS_SERIALIZE(&MacroDefinitionValidation::Toto::serialize);
		ATTRIBUTE(u);
		ATTRIBUTE(t);
	CLASS_END;


	CLASS_IMP(MacroDefinitionValidation);
		CLASS_MIGRATION(&MacroDefinitionValidation::migration);
		CLASS_VALIDATE(&MacroDefinitionValidation::validate);
		ATTRIBUTE(bo);
		ATTRIBUTE_GETSET(f,&MacroDefinitionValidation::getF,&MacroDefinitionValidation::setF);
		ATTRIBUTE(u);
		//ATTRIBUTE_NOT_SERIALIZABLE;
		ATTRIBUTE(i);
		//ATTRIBUTE_NOT_SERIALIZABLE;
		ATTRIBUTE(t);
		ATTRIBUTE(v);
		FUNCTION(&MacroDefinitionValidation::getThing);
		/*FUNCTION(&MacroDefinitionValidation::getThing1);
		FUNCTION(&MacroDefinitionValidation::getThing2);
		FUNCTION(&MacroDefinitionValidation::getThing3);
		FUNCTION(&MacroDefinitionValidation::getThing4);*/
		FUNCTION(&MacroDefinitionValidation::setThing1);
		FUNCTION(&MacroDefinitionValidation::func0);
	CLASS_END;

MAKE_TEST(FolderDBStorageUnitTest)
{
	//Save TEST
		/*{
			MacroDefinitionValidation d;
			d.bo = true;
			d.f = 1.0f;
			d.u = 3;
			d.i = -5;
			d.t.u = 4;

			BinaryStream stream("test.bb",Stream::eSaving);
			if(stream.isValid()){
				MigrationSerializer serializer(&stream);
				serializer.serialize(AbstractObject(d));
			}
		}*/

		//LOAD TEST
		/*{
			MacroDefinitionValidation d;
			BinaryStream stream("test.bb",Stream::eLoading);
			if(stream.isValid()){
				MigrationSerializer serializer(&stream);
				AbstractObject o = serializer.serialize();
				if(o.isValid()){
					d = *(o.get<MacroDefinitionValidation>());
				}
			}
		}*/

		//Delegate TEST
		/*{
			MacroDefinitionValidation d;
			Delegate del(&d,&MacroDefinitionValidation::delegateTest);
			del();
		}*/

		/*SAVE OBJECT CONTEXT TEST
		*/
		{
			FolderDBStorage s("f:\\test");
			s.clear();
			ObjectContextCoordinator::registerObjectContext("Document",new ObjectContext(&s));
			MacroDefinitionValidation* d = 
				ObjectContextCoordinator::allocate<MacroDefinitionValidation>("Document");
			s.setBootstrap(d);
			d->bo = true;
			d->f = 1.0f;
			d->u = 3;
			d->i = -5;
			d->t.u = 4;
			d->v.push_back(3);
			d->v.push_back(10);
			d->v.push_back(5);
			d->v.push_back(2);
			d->t.t = 
				ObjectContextCoordinator::allocate<MacroDefinitionValidation::Toto::Test>("Document");
			d->t.t->proxy = Proxy<Uint>(d,"t/u");

			//TODO: INFINITE LOOP here.
			//save should make sure we do not save circular references more than once !
			//ObjectContextCoordinator::saveAll();
		}

		/*LOAD OBJECT CONTEXT TEST
		*/
		/*{
			FolderDBStorage s("f:\\test");
			ObjectContextCoordinator::registerObjectContext("Document2",new ObjectContext(&s));
			Object* bootstrap = ObjectContextCoordinator::getBootstrap("Document2",true);
			if(bootstrap && bootstrap->isKindOf<MacroDefinitionValidation>()){
				MacroDefinitionValidation* m = reinterpret_cast<MacroDefinitionValidation*>(bootstrap);
				Uint res = m->t.t->proxy.get();
				//ASSERT(res == 4);
			}
		}*/
}