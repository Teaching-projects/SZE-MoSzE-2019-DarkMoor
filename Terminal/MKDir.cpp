#include "MKDir.h"
#include "terminal.h"
#include "Directory.h"
#include <sstream>
#include <iostream>

void MKDir::Execute(std::string params)
{
	if (AddDirectory(params) == nullptr)
	{
		std::cout << "Already exists!\n";
	}
}
Directory* MKDir::AddDirectory(std::string path)
{
	if (Terminal::GetInstance()->GetActual()->GetDirectory(path) == nullptr)
	{
		return Terminal::GetInstance()->GetActual()->AddDirectory(path);
	}
	return nullptr;
}
bool MKDir::ValidateParams(std::string params)
{
	return false;
}