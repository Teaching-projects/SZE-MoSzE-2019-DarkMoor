#include <string>
#include "Directory.h"

Base::Base(std::string Name, Directory* Parent)
{
	this->Name = Name;
	this->Parent = Parent;
}