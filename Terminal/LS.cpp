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
				std::cout << t << ":" << std::endl;
			}
			Base* b = GetDirectory(t);
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
	}
	ResetOptions();
}
Base* LS::GetDirectory(std::string path)
{
	return Terminal::GetInstance()->GetActual();
}
Base* LS::GetDirectoryRecursive(std::string path, Base* startDir)
{
	return nullptr;
}
void LS::ResetOptions()
{
}
bool LS::SetOptions(char c)
{
	return true;
}