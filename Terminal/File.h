#ifndef FILE_H
#define FILE_H
#include "Base.h"
#include <string>

class Directory;
class File : public Base
{
private:
	std::string content;
public:
	File(std::string Name, Directory* Parent, std::string Content = "");
	~File();
	std::string GetName() override;
	std::string GetFullName() override;
	Directory* GetParent() override;
	void SetContent(std::string content);
	void AppendContent(std::string content);
	void DeleteContent();
	std::string GetContet();
};
#endif

