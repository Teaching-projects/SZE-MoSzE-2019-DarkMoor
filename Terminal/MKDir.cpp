#include "MKDir.h"
#include "Terminal.h"
#include "Directory.h"
#include <sstream>
#include <iostream>
#include <vector>

MKDir::MKDir(std::string Name, std::string Options, int NonOptionalParams) : CommandBase(Name, Options, NonOptionalParams)
{

}

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
Directory* MKDir::AddDirectoryRecursive(std::string path, Directory* startDir)
{
	return nullptr;
}
void MKDir::ResetOptions()
{
}
bool MKDir::SetOptions(char c)
{
	return true;
}