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
	std::vector<std::string> args = GetArgs(params);
	if (!this->ValidateParams(args))
	{
		ResetOptions();
		return;
	}
	for (auto it = args.begin(); it != args.end(); )
	{
		if ((*it)[0] == '-')
		{
			it = args.erase(it);
		}
		else
		{
			++it;
		}
	}
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
}

Base* RM::GetTarget(std::string path)
{
	return Terminal::GetInstance()->GetActual()->GetDirectory(path);
}

Base* RM::GetTargetRecursive(std::string path, Base* startDir)
{
	return nullptr;
}

bool RM::ValidateParams(std::vector<std::string> args)
{
	int nonOptionParams = 0;
	for (auto a : args)
	{
		if (a[0] != '-')
		{
			nonOptionParams++;
			continue;
		}
		for (int i = 1; i < (int)a.length(); i++)
		{
			bool validoption = false;
			for (int j  = 0; j < options.length(); j++)
			{
				if (options[j] == a[i])
				{
					validoption = true;
					SetOptions(a[i]);
				}
			}
			if (!validoption)
			{
				std::cout << "Invalid option: " + a[i] << std::endl;
				return false;
			}
		}
	}
	if (nonOptionParams >= nonOptionalParams)
	{
		return true;
	}
	return false;
}

std::vector<std::string> RM::GetArgs(std::string params)
{
	std::vector<std::string> argv;
	std::stringstream ss(params);
	std::string arg;
	while (std::getline(ss, arg, ' '))
	{
		if (arg.length() != 0)
		{
			argv.push_back(arg);
		}
	}
	return argv;
}

void RM::SetForce(char c)
{
	if (c == 'f')
	{
		this->force = true;
	}
}

void RM::SetRecursive(char c)
{
	if (c == 'r')
	{
		this->recursive = true;
	}
}

void RM::SetOptions(char c)
{
	SetForce(c);
	SetRecursive(c);
}

void RM::ResetOptions()
{
	this->force = false;
	this->recursive = false;
}