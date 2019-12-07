#include "RM.h"
#include <vector>
#include <iostream>
#include "Base.h"
#include "Directory.h"
#include <sstream>
#include <string>
#include "Terminal.h"


RM::RM(std::string Name, std::string Options, int NonOptionalParams) : force(false), recursive(false), CommandBase(Name, Options, NonOptionalParams)
{
}

RM::~RM()
{

}

void RM::Execute(std::string params)
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
		RemoveDirectory(t);
	}
	ResetOptions();
}
void RM::RemoveDirectory(std::string path)
{
	std::string originalpath = path;
	Base* b = nullptr;
	Directory* dir = GetStartDirectory(path);
	if (dir == nullptr)
	{
		if (!force)
		{
			std::cout << "rm: cannot remove '" + originalpath + "': No such file or directory" << std::endl;
		}
		return;
	}
	std::vector<std::string> dirnames = SplitPath(path);
	unsigned int i = 1;
	for (auto t : dirnames)
	{
		b = dir->GetSubelement(t);
		if (b == nullptr)
		{
			if (!force)
			{
				std::cout << "rm: cannot remove '" + originalpath + "': No such file or directory" << std::endl;
			}
			return;
		}
		dir = dynamic_cast<Directory*>(b);
		if (i == dirnames.size())
		{
			if (dir != nullptr)
			{
				if (recursive)
				{
					dir->GetParent()->RemoveSubelement(dir->GetName());
				}
				else
				{
					if (!force)
					{
						std::cout << "rm: cannot remove '" + dir->GetName() + "': Is a directory" << std::endl;
					}
				}
			}
			else
			{
				b->GetParent()->RemoveSubelement(b->GetName());
			}
			return;
		}
		if (dir == nullptr)
		{
			if (!force)
			{
				std::cout << "rm: cannot remove '" + originalpath + "': Not a directory" << std::endl;
			}
			return;
		}
		i++;
	}
}

void RM::ResetOptions()
{
	this->force = false;
	this->recursive = false;
}
bool RM::SetOptions(char c)
{
	switch (c)
	{
	case 'f':
		this->force = true;
		return true;
		break;
	case 'r':
		this->recursive = true;
		return true;
		break;
	}
	return false;
}