#include "CD.h"
#include "terminal.h"
#include "Directory.h"
#include <sstream>

void CD::Execute(std::string params)
{
	Directory* dir = GetTargetDirectory(params);
	Terminal::GetInstance()->SetActual(dir);
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
	}
	return dir;
}
bool CD::ValidateParams(std::string params)
{
	return false;
}