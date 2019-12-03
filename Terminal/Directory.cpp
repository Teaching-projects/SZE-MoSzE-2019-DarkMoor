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
	if (GetSubelement(dirname) || dirname == "." || dirname == "..")
	{
		return nullptr;
	}
	Directory* dir = new Directory(dirname, this);
	SubDirectories.push_back(dir);
	return dir;
}

Base* Directory::GetSubelement(std::string dirname)
{
	if (dirname == "..")
	{
		return Parent;
	}
	if (dirname == ".")
	{
		return this;
	}
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
	if (GetSubelement(path) || path == "." || path == "..")
	{
		return nullptr;
	}
	File* file = new File(path, this);
	SubDirectories.push_back(file);
	return file;
}

Json::Value Directory::Jsonify()
{
	Json::Value v;
	v["name"] = this->Name;
	v["type"] = "directory";
	v["subelements"] = Json::Value(Json::arrayValue);
	Json::Value& subs = v["subelements"];
	int i = 0;
	for (auto s : SubDirectories)
	{
		subs[i] = s->Jsonify();
		i++;
	}
	return v;
}

void Directory::UnJsonify(Json::Value SubValues)
{
	int index = 0;
	for (Json::Value::ArrayIndex i = 0; i < SubValues.size(); i++)
	{
		if (SubValues[i].isMember("name") && SubValues[i].isMember("type"))
		{
			if (SubValues[i]["type"].asString() == "directory")
			{
				Directory* dir = new Directory(SubValues[i]["name"].asString(), this);
				SubDirectories.push_back(dir);
				if (SubValues[i].isMember("subelements"))
				{
					dir->UnJsonify(SubValues[i]["subelements"]);
				}
			}
			else if (SubValues[i]["type"].asString() == "file")
			{
				File* file = new File(SubValues[i]["name"].asString(), this);
				if (SubValues[i].isMember("content"))
				{
					file->SetContent(SubValues[i]["content"].asString());
				}
				SubDirectories.push_back(file);
			}
			else
			{
				std::cout << "UnJsonify error at sub: " + this->GetFullName() + "/" << index << std::endl;
			}
		}
		else
		{
			std::cout << "UnJsonify error at sub: " + this->GetFullName() + "/" << index << std::endl;
		}
	}
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

bool Directory::RemoveSubelement(std::string path)
{
	int i = 0;
	for (auto dir : SubDirectories)
	{
		if (dir->GetName() == path)
		{
			delete dir;
			SubDirectories.erase(SubDirectories.begin() + i);
			return true;
		}
	}
	return false;
}
