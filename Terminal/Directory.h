#ifndef  DIRECTORY_H
#define  DIRECTORY_H
#include <string>
#include "Base.h"
#include "vector"


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
	Base* GetDirectory(std::string path);
};
#endif