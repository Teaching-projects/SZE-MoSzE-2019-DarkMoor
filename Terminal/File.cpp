#include "File.h"
#include "Directory.h"
#include <string>

File::File(std::string Name, Directory* Parent):Base(Name,Parent)
{
}

File::~File()
{
	delete Parent;
}

std::string File::GetName()
{
	return this->Name;
}
Directory* File::GetParent()
{
	return this->Parent;
}
Json::Value File::Jsonify()
{
	Json::Value v;
	v["name"] = this->Name;
	v["type"] = "file";
	return v;
}
void File::UnJsonify(Json::Value SubValues)
{}
std::string File::GetFullName()
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
