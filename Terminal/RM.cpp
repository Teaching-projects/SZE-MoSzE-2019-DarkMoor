#include "RM.h"
#include <vector>
#include <iostream>
#include "Base.h"
#include "Directory.h"
#include <sstream>
#include <string>
#include "Terminal.h"


RM::RM(std::string Name, std::string Options, int NonOptionalParams) : CommandBase(Name, Options, NonOptionalParams)
{
	this->force = false;
	this->recursive = false;
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
		Base* target = GetTarget(t);
		if (target != nullptr)
		{
			Directory* dir = dynamic_cast<Directory*>(target);
			if (dir != nullptr)
			{
				if (recursive)
				{
					dir->GetParent()->RemoveDirectory(dir->GetName());
				}
				else
				{
					if (!force)
					{
						std::cout << "rm: cannot remove '" + target->GetName() + "': Is a directory" << std::endl;
					}
				}
			}
			else
			{
				target->GetParent()->RemoveDirectory(target->GetName());
			}
		}
		else
		{
			if (!force)
			{
				std::cout << "rm: cannot remove '" + t + "' : No such file or directory" << std::endl;
			}
		}
	}
	ResetOptions();
}
Base* RM::GetTarget(std::string path)
{
	return Terminal::GetInstance()->GetActual()->GetDirectory(path);
}
Base* RM::GetTargetRecursive(std::string path, Base* startDir)
{
	return nullptr;
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