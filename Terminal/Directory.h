#ifndef  DIRECTORY_H
#define  DIRECTORY_H
#include <string>
#include "Base.h"
#include "vector"
#include "json/json.h"

class File;
class Directory : public Base
{
private:
	std::vector<Base*> SubDirectories;
public:
	Directory(std::string Name, Directory* Parent);
	~Directory();
	std::string GetFullName() override;
	Directory* AddDirectory(std::string path);
	void ListDirectories();
	bool RemoveSubelement(std::string path, bool perma = true);
	Base* GetSubelement(std::string path);
	File* AddFile(std::string path);
	bool MoveElement(Base* MovableObject, std::string Name);
	Json::Value Jsonify() override;
	void UnJsonify(Json::Value SubValues) override;
};
#endif