#include "MKDir.h"
#include "terminal.h"
#include "Directory.h"
#include <sstream>

void MKDir::Execute(std::string params)
{
	AddDirectory(params);
}
Directory* MKDir::AddDirectory(std::string path)
{
	return Terminal::GetInstance()->GetActual()->AddDirectory(path);
}
bool MKDir::ValidateParams(std::string params)
{
	return false;
}