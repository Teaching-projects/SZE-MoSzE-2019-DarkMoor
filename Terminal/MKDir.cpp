#include "MKDir.h"
#include "Terminal.h"
#include "Directory.h"
#include <sstream>
#include <iostream>
#include <vector>

MKDir::MKDir(std::string Name, std::string Options, int NonOptionalParams) : CommandBase(Name, Options, NonOptionalParams)
{

}

void MKDir::Execute(std::string params)
{
	std::vector<std::string> args = this->GetArgs(params);
	if (!this->ValidateParams(args))
	{
		ResetOptions();
		return;
	}
	args = RemoveOptions(args); 
	for (auto t : args)
	{
		AddDirectory(t);
	}
}
void MKDir::AddDirectory(std::string path)
{
	std::string originalpath = path;
	Base* b = nullptr;
	Directory* dir = GetStartDirectory(path);
	if (dir == nullptr)
	{
		std::cout << "mkdir: cannot create directory '" + originalpath + "': No such file or directory" << std::endl;
		return;
	}
	std::vector<std::string> dirnames = SplitPath(path);
	unsigned int i = 1;
	for (auto t : dirnames)
	{
		if (i == dirnames.size())
		{
			if (!dir->AddDirectory(t))
			{
				std::cout << "cannot create directory '" + originalpath + "': File exists" << std::endl;
			}
			return;
		}
		b = dir->GetSubelement(t);
		if (b == nullptr)
		{
			std::cout << "mkdir: cannot create directory '" + originalpath + "': No such file or directory" << std::endl;
			return;
		}
		dir = dynamic_cast<Directory*>(b);
		if (dir == nullptr)
		{
			std::cout << "mkdir: cannot create directory '" + originalpath + "': Not a directory" << std::endl;
			return;
		}
		i++;
	}
}
void MKDir::ResetOptions()
{
}
bool MKDir::SetOptions(char c)
{
	return true;
}