#include "LS.h"
#include "Terminal.h"
#include "Base.h"
#include "Directory.h"
#include <sstream>
#include <vector>
#include <iostream>

LS::LS(std::string Name, std::string Options, int NonOptionalParams) : CommandBase(Name, Options, NonOptionalParams)
{

}

void LS::Execute(std::string params)
{
	std::vector<std::string> args = this->GetArgs(params);
	if (!this->ValidateParams(args))
	{
		ResetOptions();
		return;
	}
	args = RemoveOptions(args);
	if (args.size() == 0)
	{
		Terminal::GetInstance()->GetActual()->ListDirectories();
	}
	else
	{
		for (auto t : args)
		{
			if (args.size() > 1)
			{
				std::cout << t  << ":" << std::endl;
				GetDirectory(t);
				std::cout << std::endl;
			}
			else
			{
				GetDirectory(t);
			}
		}
	}
	ResetOptions();
}
void LS::GetDirectory(std::string path)
{
	std::string originalpath = path;
	Base* b = nullptr;
	Directory* dir = GetStartDirectory(path);
	if (dir == nullptr)
	{
		std::cout << "ls: cannot access '" + originalpath + "': No such file or directory" << std::endl;
		return;
	}
	std::vector<std::string> dirnames = SplitPath(path);
	unsigned int i = 1;
	for (auto t : dirnames)
	{
		b = dir->GetSubelement(t);
		if (b == nullptr)
		{
			std::cout << "ls: cannot access '" + originalpath + "': No such file or directory" << std::endl;
			return;
		}
		dir = dynamic_cast<Directory*>(b);
		if (dir == nullptr)
		{
			std::cout << "ls: cannot access '" + originalpath + "': Not a directory" << std::endl;
			return;
		}
		if (i == dirnames.size())
		{
			dir->ListDirectories();
			return;
		}
		i++;
	}
}
void LS::ResetOptions()
{
}
bool LS::SetOptions(char c)
{
	return true;
}