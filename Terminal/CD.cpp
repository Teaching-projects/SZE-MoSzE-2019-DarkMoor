#include "CD.h"
#include "terminal.h"
#include "Directory.h"
#include <sstream>
#include <iostream>

void CD::Execute(std::string params)
{
	Directory* dir = GetTargetDirectory(params);
	if (dir != nullptr) {
		Terminal::GetInstance()->SetActual(dir);
	}
}
Directory* CD::GetTargetDirectory(std::string path)
{
	Directory* dir = nullptr;
	if (path == "..")
	{
		dir = Terminal::GetInstance()->GetActual()->GetParent();
	}
	else 
	{
		dir = Terminal::GetInstance()->GetActual()->GetDirectory(path);
		if (dir == nullptr) {
			std::cout << "Directory doesn't exists!\n";
		}
	}
	return dir;
}
bool CD::ValidateParams(std::string params)
{
	return false;
}