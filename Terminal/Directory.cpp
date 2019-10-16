#include "Directory.h"
#include <string>
#include <iostream>

std::string Directory::GetFullName()
{
	if (this->Parent != nullptr)
	{
		if (this->Parent->GetParent() != nullptr)
		{
			return Parent->GetFullName() + "/" + this->Name;
		}
		else
		{
			return Parent->GetFullName() + this->Name;
		}
	}
	return this->Name;
}
std::string Directory::GetName()
{
	return this->Name;
}
Directory* Directory::GetParent()
{
	return this->Parent;
}

Directory* Directory::AddDirectory(std::string dirname)
{
	Directory* dir = new Directory(dirname, this);
	SubDirectories.push_back(dir);
	return dir;
}

Directory* Directory::GetDirectory(std::string dirname)
{
	for (auto dir : SubDirectories)
	{
		Directory* castedDir = dynamic_cast<Directory*>(dir);
		if (castedDir != nullptr)
		{
			if (dir->GetName() == dirname)
			{
				return castedDir;
			}
		}
	}
	return nullptr;
}

void Directory::ListDirectories()
{
	for (Base* item : SubDirectories)
	{
		Directory* dir = dynamic_cast<Directory*>(item);
		if (dir != nullptr)
		{
			std::cout << dir->GetName() << "\t" << "dir \n";
		}
		else
		{
			std::cout << item->GetName() << "\t" << "file \n";
		}
	}
}