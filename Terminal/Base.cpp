#include <string>
#include "Directory.h"
#include "Base.h"

Base::Base(std::string Name, Directory* Parent)
{
	this->Name = Name;
	this->Parent = Parent;
}
Base::~Base(){}

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

bool Base::IsChildOf(Directory* dir)
{
	if (dir == nullptr) return false;
	if (dir == this) return true;
	if (Parent == nullptr) return false;
	if (dir == Parent)
	{
		return true;
	}
	return Parent->IsChildOf(dir);
}