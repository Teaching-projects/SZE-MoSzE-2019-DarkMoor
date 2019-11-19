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
		if (AddFile(t) == nullptr)
		{
			std::cout << "Cannot create file '" + t + "': File exists" << std::endl;
		}
	}
}

File* Touch::AddFile(std::string path)
{
	if (Terminal::GetInstance()->GetActual()->GetSubelement(path) == nullptr)
	{
		return Terminal::GetInstance()->GetActual()->AddFile(path);
	}
	return nullptr;
}

File* Touch::AddFileRecursive(std::string path, Base* startDir)
{
	return nullptr;
}

void Touch::ResetOptions()
{
}

bool Touch::SetOptions(char c)
{
	return true;
}