#include "Echo.h"
#include "Terminal.h"
#include "Directory.h"
#include <sstream>
#include <iostream>
#include <vector>

Echo::Echo(std::string Name, std::string Options, int NonOptionalParams) : CommandBase(Name, Options, NonOptionalParams)
{
}

void Echo::Execute(std::string params)
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
		std::cout << t << std::endl;
	}
}
void Echo::ResetOptions()
{
}

bool Echo::SetOptions(char c)
{
	return true;
}
