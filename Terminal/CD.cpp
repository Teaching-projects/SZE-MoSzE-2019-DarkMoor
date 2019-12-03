#include "CD.h"
#include "Terminal.h"
#include "Directory.h"
#include "Base.h"
#include <sstream>
#include <iostream>
#include <vector>

CD::CD(std::string Name, std::string Options, int NonOptionalParams) : CommandBase(Name, Options, NonOptionalParams)
{

}

void CD::Execute(std::string params)
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
		SetActuallDirectory(t);
		return;
	}
}
void CD::SetActuallDirectory(std::string path)
{
	std::string originalpath = path;
	Base* b = nullptr;
	Directory* dir = GetStartDirectory(path);
	if (dir == nullptr)
	{
		std::cout << "cd: '" + originalpath + "': No such file or directory" << std::endl;
		return;
	}
	std::vector<std::string> dirnames = SplitPath(path);
	int i = 1;
	for (auto t : dirnames)
	{
		b = dir->GetSubelement(t);
		if (b == nullptr)
		{
			std::cout << "cd: '" + originalpath + "': No such file or directory" << std::endl;
			return;
		}
		dir = dynamic_cast<Directory*>(b);
		if (dir == nullptr)
		{
			std::cout << "cd: '" + originalpath + "': Not a directory" << std::endl;
			return;
		}
		if (i == dirnames.size())
		{
			Terminal::GetInstance()->SetActual(dir);
			return;
		}
		i++;
	}
}
void CD::ResetOptions()
{
}
bool CD::SetOptions(char c)
{
	return true;
}