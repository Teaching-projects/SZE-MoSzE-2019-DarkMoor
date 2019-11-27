#include <string>
#include "Directory.h"
#include "Base.h"

Base::Base(std::string Name, Directory* Parent)
{
	this->Name = Name;
	this->Parent = Parent;
}

Directory* Base::GetParent()
{
	return this->Parent;
}

void Base::SetParent(Directory* Parent)
{
	this->Parent = Parent;
}

std::string Base::GetName()
{
	return this->Name;
}
void Base::SetName(std::string Name)
{
	this->Name = Name;
}