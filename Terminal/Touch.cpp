#include "Base.h"
#include "Touch.h"
#include "Terminal.h"
#include "Directory.h"
#include "File.h"
#include <string>
#include <iostream>
#include <vector>

Touch::Touch(std::string Name, std::string Options, int NonOptionalParams) : CommandBase(Name, Options, NonOptionalParams)
{
}

void Touch::Execute(std::string params)
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
		AddFile(t);
	}
}

void Touch::AddFile(std::string path)
{
	std::string originalpath = path;
	Base* b = nullptr;
	Directory* dir = GetStartDirectory(path);
	if (dir == nullptr)
	{
		std::cout << "touch: cannot create file '" + originalpath + "': No such file or directory" << std::endl;
		return;
	}
	std::vector<std::string> dirnames = SplitPath(path);
	int i = 1;
	for (auto t : dirnames)
	{
		if (i == dirnames.size())
		{
			if (!dir->AddFile(t))
			{
				std::cout << "touch: cannot create file '" + originalpath + "': File exists" << std::endl;
				return;
			}
		}
		b = dir->GetSubelement(t);
		if (b == nullptr)
		{
			std::cout << "touch: cannot create file '" + originalpath + "': No such file or directory" << std::endl;
			return;
		}
		dir = dynamic_cast<Directory*>(b);
		if (dir == nullptr)
		{
			std::cout << "touch: cannot create file '" + originalpath + "': Not a directory" << std::endl;
			return;
		}
		i++;
	}
}
void Touch::ResetOptions()
{
}

bool Touch::SetOptions(char c)
{
	return true;
}