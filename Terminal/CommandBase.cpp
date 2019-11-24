#include "CommandBase.h"
#include "Directory.h"
#include "Terminal.h"
#include <iostream>
#include <sstream>
#include <string>

CommandBase::CommandBase(std::string Name, std::string Options, int NonOptionalParams)
{
	this->options = Options;
	this->nonOptionalParams = NonOptionalParams;
	this->name = Name;
}

std::string CommandBase::GetName()
{
	return this->name;
}

std::string CommandBase::Trim(std::string str)
{
	std::string chars = "\t\n\v\f\r ";
	str.erase(0, str.find_first_not_of(chars));
	str.erase(str.find_last_not_of(chars) + 1);
	return str;
}

std::vector<std::string> CommandBase::GetArgs(std::string params)
{
	std::vector<std::string> argv;
	std::stringstream ss(params);
	std::string arg;
	while (std::getline(ss, arg, ' '))
	{
		arg = Trim(arg);
		if (arg.length() != 0)
		{
			argv.push_back(arg);
		}
	}
	return argv;
}

std::vector<std::string> CommandBase::RemoveOptions(std::vector<std::string> args)
{
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
	return args;
}

bool CommandBase::ValidateParams(std::vector<std::string> args)
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
			if (!SetOptions(a[i]))
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
	std::cout << "Not enough parameter! Needed " << nonOptionalParams << ", got " << nonOptionParams << "." << std::endl;
	return false;
}

Directory* CommandBase::GetStartDirectory(std::string path)
{
	if (path.length() > 1 && path[0] != '.' && path[0] != '/' || path.length() > 2 && path.substr(0, 2) == "./")
	{
		return Terminal::GetInstance()->GetActual();
	}
	if (path.length() > 1 && path[0] == '/')
	{
		return Terminal::GetInstance()->GetRoot();
	}
	if (path.length() > 3 && path.substr(0, 3) == "../")
	{
		return Terminal::GetInstance()->GetActual()->GetParent();
	}
	return nullptr;
}