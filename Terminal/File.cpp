#include "File.h"
#include "Directory.h"
#include <string>

File::File(std::string Name, Directory* Parent, std::string Content):Base(Name,Parent)
{
	this->content = Content;
}

File::~File()
{
}

Json::Value File::Jsonify()
{
	Json::Value v;
	v["name"] = this->Name;
	v["type"] = "file";
	v["content"] = content;
	return v;
}
void File::UnJsonify(Json::Value SubValues)
{}
void File::SetContent(std::string content)
{
	this->content = content;
}
void File::AppendContent(std::string content)
{
	this->content += content;
}
void File::DeleteContent()
{
	content = "";
}
std::string File::GetContet()
{
	return content;
}
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
