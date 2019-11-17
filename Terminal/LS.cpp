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
	if (params.length() < 1)
	{
		Terminal::GetInstance()->GetActual()->ListDirectories();
		return;
	}
	Base* b = GetDirectory(params);
	if (b != nullptr)
	{
		Directory* dir = dynamic_cast<Directory*>(b);
		if (dir != nullptr)
		{
			dir->ListDirectories();
		}
		else
		{
			std::cout << "Not a directory!" << std::endl;
		}
	}
	else
	{
		std::cout << "No such file or directory!" << std::endl;
	}
}
Base* LS::GetDirectory(std::string path)
{
	return Terminal::GetInstance()->GetActual();
}
Base* LS::GetDirectoryRecursive(std::string path, Base* startDir)
{
	return nullptr;
}
bool LS::ValidateParams(std::vector<std::string> args)
{
	return false;
}