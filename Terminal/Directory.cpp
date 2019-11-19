#include "Directory.h"
#include "File.h"
#include <string>
#include <iostream>

Directory::Directory(std::string Name, Directory* Parent) : Base(Name, Parent)
{

}

Directory::~Directory()
{
	for (auto dir : SubDirectories)
	{
		delete dir;
	}
	delete Parent;
}

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

Base* Directory::GetSubelement(std::string dirname)
{
	for (auto dir : SubDirectories)
	{
		if (dir->GetName() == dirname)
		{
			return dir;
		}
	}
	return nullptr;
}

File* Directory::AddFile(std::string path)
{
	File* file = new File (path, this);
	SubDirectories.push_back(file);
	return file;
}

void Directory::ListDirectories()
{
	for (Base* item : SubDirectories)
	{
		Directory* dir = dynamic_cast<Directory*>(item);
		if (dir != nullptr)
		{
			std::cout << dir->GetName() << "\t" << "dir" << std::endl;
		}
		else
		{
			std::cout << item->GetName() << "\t" << "file" << std::endl;
		}
	}
}

void Directory::RemoveDirectory(std::string path)
{
	int i = 0;
	for (auto dir : SubDirectories)
	{
		if (dir->GetName() == path)
		{
			delete dir;
			SubDirectories.erase(SubDirectories.begin() + i);
		}
	}
}
