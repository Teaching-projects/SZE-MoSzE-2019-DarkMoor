#include "Exit.h"
#include "Terminal.h"
#include <vector>

Exit::Exit(std::string Name, std::string Options, int NonOptionalParams) : CommandBase(Name, Options, NonOptionalParams)
{

}

void Exit::Execute(std::string params)
{
	Terminal::GetInstance()->SetExit(true);
}

bool Exit::ValidateParams(std::vector<std::string> args)
{
	return true;
}