#include "LS.h"
#include "terminal.h"
#include "Directory.h"
#include <sstream>

void LS::Execute(std::string params)
{
	if (params.length() < 1)
	{
		Terminal::GetInstance()->GetActual()->ListDirectories();
		return;
	}
	Directory* dir = GetDirectory(params);
	if (dir != nullptr)
	{
		dir->ListDirectories();
	}
}
Directory* LS::GetDirectory(std::string path)
{
	return Terminal::GetInstance()->GetActual()->GetDirectory(path);
}
bool LS::ValidateParams(std::string params)
{
	return false;
}