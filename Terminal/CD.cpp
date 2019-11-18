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
	Directory* dir = GetTargetDirectory(params);
	if (dir != nullptr) {
		Terminal::GetInstance()->SetActual(dir);
	}
}
Directory* CD::GetTargetDirectory(std::string path)
{
	Base* b = nullptr;
	if (path == "..")
	{
		b = Terminal::GetInstance()->GetActual()->GetParent();
	}
	else 
	{
		b = Terminal::GetInstance()->GetActual()->GetDirectory(path);
	}
	if (b == nullptr)
	{
		std::cout << "Directory doesn't exists!\n";
	}
	Directory* dir = dynamic_cast<Directory*>(b);
	if (dir == nullptr)
	{
		std::cout << "Not a directory!" << std::endl;
	}
	return dir;
}
Directory* CD::GetTargetDirectoryRecursive(std::string path, Directory* startDir)
{
	return nullptr;
}
void CD::ResetOptions()
{
}
bool CD::SetOptions(char c)
{
	return true;
}