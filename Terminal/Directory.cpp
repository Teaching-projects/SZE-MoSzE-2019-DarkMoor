#include "Directory.h"
#include "Terminal.h"
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

bool Directory::MoveElement(Base* MovableObject, std::string Name)
{
	if (Name == "." || Name == "..") return false;
	if (MovableObject == nullptr) return false;
	Directory* dir = MovableObject->GetParent();
	if (!dir || IsChildOf(dynamic_cast<Directory*>(MovableObject))) return false;
	Base* sub = GetSubelement(Name);
	if (sub != MovableObject)
	{
		if (dynamic_cast<File*>(sub) && dynamic_cast<File*>(MovableObject)) RemoveSubelement(Name);
		else if (dynamic_cast<Directory*>(sub) && dynamic_cast<File*>(MovableObject) || dynamic_cast<Directory*>(sub) && dynamic_cast<Directory*>(MovableObject)) return false;
	}
	dir->RemoveSubelement(MovableObject->GetName(), false);
	SubDirectories.push_back(MovableObject);
	MovableObject->SetParent(this);
	MovableObject->SetName(Name);
	return true;
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

bool Directory::RemoveSubelement(std::string path, bool perma)
{
	int i = 0;
	for (auto dir : SubDirectories)
	{
		if (dir->GetName() == path)
		{
			if (Terminal::GetInstance()->GetActual()->IsChildOf(dynamic_cast<Directory*>(dir))) return false;
			if (perma) delete dir;
			SubDirectories.erase(SubDirectories.begin() + i);
			return true;
		}
		i++;
	}
	return false;
}
