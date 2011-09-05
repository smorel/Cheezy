CLASS_IMP(FolderDBStorage);
CLASS_END;

CLASS_IMP(FolderDBStorage::ObjectSerializer);
CLASS_END;


void FolderDBStorage::ObjectSerializer::save(Object* o,const std::string& path){
	BinaryStream stream(path,Stream::eSaving);
	//Save additional infos
	if(stream.isValid()){
		MigrationSerializer serializer(&stream);
		serializer.serialize(AbstractObject(o));
	}
}

Object* FolderDBStorage::ObjectSerializer::load(const std::string& path){
	BinaryStream stream(path,Stream::eLoading);
	//Read additional infos
	if(stream.isValid()){
		MigrationSerializer serializer(&stream);
		AbstractObject o = serializer.serialize();
		if(o.isValid() && o.isKindOf<Object>()){
			return o.get<Object>();
		}
	}
	return 0;
}

Boolean FolderDBStorage::ObjectSerializer::exists(const std::string& path){
	BinaryStream stream(path,Stream::eLoading);
	return stream.isValid();
}

FolderDBStorage::FolderDBStorage(){
}

FolderDBStorage::FolderDBStorage(const std::string& _path)
: path(_path){
	_loadBootstrap();
}

Boolean FolderDBStorage::ownObject(const ID& id){
	std::string path = _filePath(id);
	ObjectSerializer s;
	return s.exists(path);
}

Object* FolderDBStorage::loadObject(const ID& id){
	std::string path = _filePath(id);
	ObjectSerializer s;
	return s.load(path);
}

void FolderDBStorage::saveObject(Object* o){
	_ensureFolderExists();
	std::string path = _filePath(o->getId());
	ObjectSerializer s;
	return s.save(o,path);
}

std::string FolderDBStorage::getName(const ID& id){
	//read header and return name
	return "";
}

const Descriptor* FolderDBStorage::getDescriptor(const ID& id){
	//read header and return descriptor
	return 0;
}

Boolean FolderDBStorage::_requestEdition(Object* o){
	//check in source control if the associated file is available && data version is ok
	return true;
}

void FolderDBStorage::saveAll(){
	_saveBootstrap();
	for(std::set<Object*>::iterator it = editedObjects.begin(); it != editedObjects.end(); ++it){
		saveObject(*it);
	}
	editedObjects.clear();
}

std::string FolderDBStorage::_filePath(const ID& id){
	std::string ret = path + "\\";
	ret += id.toString();
	ret += ".simple.binary";
	return ret;
}

std::string FolderDBStorage::_bootstrapPath(){
	std::string ret = path + "\\";
	ret += "bootstrap";
	return ret;
}

void FolderDBStorage::_loadBootstrap(){
	BinaryStream stream(_bootstrapPath(),Stream::eLoading);
	if(stream.isValid()){
		MigrationSerializer serializer(&stream);
		AbstractObject o = serializer.serialize();
		if(o.isValid() && o.isKindOf<ID>()){
			bootstrap = *(o.get<ID>());
		}
	}
}

void FolderDBStorage::_saveBootstrap(){
	_ensureFolderExists();
	//verify if file change ...
	//if changed save and checkout or add file in source control
	BinaryStream stream(_bootstrapPath(),Stream::eSaving);
	if(stream.isValid()){
		MigrationSerializer serializer(&stream);
		serializer.serialize(AbstractObject(bootstrap));
	}
}

namespace FolderDBStorage_CPP{
	int DeleteDirectory(const std::string& path, bool bDeleteSubdirectories = true){
	  bool            bSubdirectory = false;       // Flag, indicating whether
												   // subdirectories have been found
	  HANDLE          hFile;                       // Handle to directory
	  std::string     strFilePath;                 // Filepath
	  std::string     strPattern;                  // Pattern
	  WIN32_FIND_DATA FileInformation;             // File information


	  strPattern = path + "\\*.*";
	  hFile = ::FindFirstFile(strPattern.c_str(), &FileInformation);
	  if(hFile != INVALID_HANDLE_VALUE)
	  {
		do
		{
		  if(FileInformation.cFileName[0] != '.')
		  {
			strFilePath.erase();
			strFilePath = path + "\\" + FileInformation.cFileName;

			if(FileInformation.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
			  if(bDeleteSubdirectories)
			  {
				// Delete subdirectory
				int iRC = FolderDBStorage_CPP::DeleteDirectory(strFilePath, bDeleteSubdirectories);
				if(iRC)
				  return iRC;
			  }
			  else
				bSubdirectory = true;
			}
			else
			{
			  // Set file attributes
			  if(::SetFileAttributes(strFilePath.c_str(),
									 FILE_ATTRIBUTE_NORMAL) == FALSE)
				return ::GetLastError();

			  // Delete file
			  if(::DeleteFile(strFilePath.c_str()) == FALSE)
				return ::GetLastError();
			}
		  }
		} while(::FindNextFile(hFile, &FileInformation) == TRUE);

		// Close handle
		::FindClose(hFile);

		DWORD dwError = ::GetLastError();
		if(dwError != ERROR_NO_MORE_FILES)
		  return dwError;
		else
		{
		  if(!bSubdirectory)
		  {
			// Set directory attributes
			if(::SetFileAttributes(path.c_str(),
								   FILE_ATTRIBUTE_NORMAL) == FALSE)
			  return ::GetLastError();

			// Delete directory
			if(::RemoveDirectory(path.c_str()) == FALSE)
			  return ::GetLastError();
		  }
		}
	  }

	  return 0;
	}
}

//delete non empty directory recrsively
void FolderDBStorage::clear(){
	FolderDBStorage_CPP::DeleteDirectory(path);
}

void FolderDBStorage::_ensureFolderExists(){
	CreateDirectory(path.c_str(),NULL);
}