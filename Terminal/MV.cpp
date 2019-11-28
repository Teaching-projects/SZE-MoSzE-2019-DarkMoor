#include "MV.h"
#include "Terminal.h"
#include "Directory.h"
#include <sstream>
#include <iostream>
#include <vector>

MV::MV(std::string Name, std::string Options, int NonOptionalParams) : CommandBase(Name, Options, NonOptionalParams)
{}

MV::~MV()
{}

void MV::Execute(std::string params)
{
	std::vector<std::string> args = this->GetArgs(params);
	if (!this->ValidateParams(args))
	{
		ResetOptions();
		return;
	}
	args = RemoveOptions(args);
	MoveElement(args[0], args[1]);
}

void MV::MoveElement(std::string source, std::string target)
{
	Base* s = GetSource(source);
	if (!s) return;
	std::string originalsource = source;
	std::string originaltarget = target;
	Base* b = nullptr;
	Directory* dir = GetStartDirectory(target);
	if (dir == nullptr)
	{
		std::cout << "mv: cannot stat '" + originaltarget + "': No such file or directory" << std::endl;
		return;
	}
	Directory* last = dir;
	std::vector<std::string> dirnames = SplitPath(target);
	int i = 1;
	for (auto t : dirnames)
	{
		b = dir->GetSubelement(t);
		if (b == nullptr)
		{
			if (dirnames.size() != i)
			{
				std::cout << "mv: cannot stat '" + originaltarget + "': No such file or directory" << std::endl;
				return;
			}
			dir->MoveElement(s, t);
			return;
		}
		dir = dynamic_cast<Directory*>(b);
		if (dir == nullptr)
		{
			if (dirnames.size() != i)
			{
				std::cout << "mv: failed to access '" + originaltarget + "': Not a directory" << std::endl;
				return;
			}
			if (dynamic_cast<Directory*>(s))
			{
				std::cout << "mv: cannot overwrite non - directory '" + originaltarget + "' with directory '" + originalsource + "'" << std::endl;
				return;
			}
			last->MoveElement(s, t);
			return;
		}
		else if (dirnames.size() == i)
		{
			dir->MoveElement(s, s->GetName());
		}
		last = dir;
		i++;
	}
}

Base* MV::GetSource(std::string path)
{
	std::string originalpath = path;
	Base* b = nullptr;
	Directory* dir = GetStartDirectory(path);
	if (dir == nullptr)
	{
		std::cout << "mv: cannot stat '" + originalpath + "': No such file or directory" << std::endl;
		return nullptr;
	}
	std::vector<std::string> dirnames = SplitPath(path);
	int i = 1;
	for (auto t : dirnames)
	{
		b = dir->GetSubelement(t);
		if (b == nullptr)
		{
			std::cout << "mv: cannot stat '" + originalpath + "': No such file or directory" << std::endl;
			return nullptr;
		}
		if (dirnames.size() != i)
		{
			dir = dynamic_cast<Directory*>(b);
			if (dir == nullptr)
			{
				std::cout << "mkdir: failed to access '" + originalpath + "': Not a directory" << std::endl;
				return nullptr;
			}
		}
		i++;
	}
	return b;
}

void MV::ResetOptions()
{}

bool MV::SetOptions(char c)
{
	return true;
}
