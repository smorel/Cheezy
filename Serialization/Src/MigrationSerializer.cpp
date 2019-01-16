
	CLASS_IMP(MigrationSerializer);
	CLASS_END;

	MigrationSerializer::MigrationSerializer()
		: ISerializer(){
	}

	MigrationSerializer::MigrationSerializer(Stream* _stream)
		: ISerializer(_stream){
	}

	
	void MigrationSerializer::getAttributes(const Descriptor* d,std::set<const Attribute*>& allAttributes) const{
		if(d->getParentDescriptor()){
			getAttributes(d->getParentDescriptor(),allAttributes);
		}

		const Descriptor::OrderedAttributes& atts = d->getAttributes();
		for(Descriptor::OrderedAttributes::size_type i=0;i<atts.size();++i){
			const Attribute* attribute = atts[i];
			if(attribute->extension->serializable){
				allAttributes.insert(attribute);
			}
		}
	}

	void MigrationSerializer::serializeAttributes(const AbstractObject& o) const{
		std::set<const Attribute*> allAttributes;
		const Descriptor* d = o.getDescriptor();
		getAttributes(d,allAttributes);

		Uint attributeCount = allAttributes.size();
		stream->serializeSectionCount(attributeCount);

		switch(stream->getType()){
		case Stream::eLoading:
			{
				for(Uint i=0;i<attributeCount;++i){
					std::string attributeName;
					stream->beginSection(attributeName);

					std::string descName;
					stream->serialize(descName,"Type");
					const Descriptor* attributeDescriptor = ReflectionManager::getDescriptor(descName);
					if(!attributeDescriptor){
						//ASSERT
					}

					const Attribute* attribute = d->getAttribute(attributeName);
					if(attribute && attributeDescriptor == attribute->getDescriptor()){
						const AbstractObject attObj = attribute->get(o.getAdress());
						DescriptorSerializationExtension* serializationExt = attributeDescriptor->extension->GetOrCreateExtension<DescriptorSerializationExtension>();
						serializationExt->serialize(attObj.getAdress(),this);
					}
					else{
						if(attribute){
							MigrationAttributeTypeChange m;
							m.attribute = attribute;
							m.value = Variant(0,attributeDescriptor);
							DescriptorSerializationExtension* serializationExt = attributeDescriptor->extension->GetOrCreateExtension<DescriptorSerializationExtension>();
							serializationExt->serialize(m.value.getAdress(),this);

							DescriptorMigrationExtension* migrationExt = attributeDescriptor->extension->GetOrCreateExtension<DescriptorMigrationExtension>();
							migrationExt->migration(o.getAdress(),&m);
						}
						else{
							MigrationAttributeLost m;
							m.attributeName = attributeName;
							m.value = Variant(0,attributeDescriptor);
							DescriptorSerializationExtension* serializationExt = attributeDescriptor->extension->GetOrCreateExtension<DescriptorSerializationExtension>();
							serializationExt->serialize(m.value.getAdress(),this);

							DescriptorMigrationExtension* migrationExt = attributeDescriptor->extension->GetOrCreateExtension<DescriptorMigrationExtension>();
							migrationExt->migration(o.getAdress(),&m);
						}
					}

					 //found attribute
					allAttributes.erase(attribute);
					
					stream->endSection();
				}

				for(std::set<const Attribute*>::iterator it = allAttributes.begin();it != allAttributes.end(); ++it){
					const Attribute* attribute = *it;

					MigrationAttributeNotInData m;
					m.attribute = attribute;
					DescriptorMigrationExtension* migrationExt = d->extension->GetOrCreateExtension<DescriptorMigrationExtension>();
					migrationExt->migration(o.getAdress(),&m);
				}

				break;
			}
		case Stream::eSaving:
			{
				for(std::set<const Attribute*>::iterator it = allAttributes.begin(); it != allAttributes.end(); ++it){
					const Attribute* attribute = *it;
					std::string attributeName = attribute->getName();//not optimal to check !!!
					stream->beginSection(attributeName);
					std::string descName = attribute->getDescriptor()->getName();//not optimal to check !!!
					stream->serialize(descName,"Type");
					const AbstractObject attObj = attribute->get(o.getAdress());
					DescriptorSerializationExtension* serializationExt = attribute->getDescriptor()->extension->GetOrCreateExtension<DescriptorSerializationExtension>();
					serializationExt->serialize(attObj.getAdress(),this);
					stream->endSection();
				}
				break;
			}
		}
	}

	AbstractObject MigrationSerializer::serialize(const AbstractObject& o) const{
		AbstractObject returnValue;
		switch(stream->getType()){
			case Stream::eLoading:
				{
					std::string descName;
					stream->beginSection(descName);
					const Descriptor* desc = ReflectionManager::getInstance()->getDescriptor(descName);
					if(!desc){
						//ASSERT
					}
					else{
						void* owner = desc->allocate();
						returnValue.set(owner,desc);
						DescriptorSerializationExtension* serializationExt = desc->extension->GetOrCreateExtension<DescriptorSerializationExtension>();
						serializationExt->serialize(owner,this);
					}
					stream->endSection();
					break;
				}
			case Stream::eSaving:
				{
					std::string descName = o.getDescriptor()->getName();//not optimal to check !!!
					stream->beginSection(descName);
					DescriptorSerializationExtension* serializationExt = o.getDescriptor()->extension->GetOrCreateExtension<DescriptorSerializationExtension>();
					serializationExt->serialize(o.getAdress(),this);
					stream->endSection();
					returnValue = o;
					break;
				}
		}
		return returnValue;
	}
