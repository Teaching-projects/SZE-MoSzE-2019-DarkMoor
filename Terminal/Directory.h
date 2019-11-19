#ifndef  DIRECTORY_H
#define  DIRECTORY_H
#include <string>
#include "Base.h"
#include "vector"

class File;
class Directory : public Base
{
private:
	std::vector<Base*> SubDirectories;
public:
	Directory(std::string Name, Directory* Parent);
	~Directory();
	std::string GetName() override;
	std::string GetFullName() override;
	Directory* GetParent() override;
	Directory* AddDirectory(std::string path);
	void ListDirectories();
	void RemoveDirectory(std::string path);
	Base* GetSubelement(std::string path);
	File* AddFile(std::string path);
};
#endif