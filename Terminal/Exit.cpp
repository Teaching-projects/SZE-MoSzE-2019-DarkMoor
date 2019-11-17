#include "Exit.h"
#include "Terminal.h"

void Exit::Execute(std::string params)
{
	Terminal::GetInstance()->SetExit(true);
}

bool Exit::ValidateParams(std::string params)
{
	return true;
}