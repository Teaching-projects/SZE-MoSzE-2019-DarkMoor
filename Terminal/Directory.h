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
	Directory(std::string Name, Directory* Parent) :Base(Name, Parent)
	{
	}
	~Directory()
	{
		delete Parent;
		for (auto dir : SubDirectories)
		{
			delete dir;
		}
	}
	std::string GetName() override;
	std::string GetFullName() override;
	Directory* GetParent();
	Directory* AddDirectory(std::string path);
	void ListDirectories();
	Directory* GetDirectory(std::string path);
};
#endif