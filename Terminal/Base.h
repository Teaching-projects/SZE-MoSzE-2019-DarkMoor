#ifndef BASE_H
#define BASE_H
#include <string>
class Directory;
class Base
{
protected:
	std::string Name;
	Directory* Parent;
public:
	Base(std::string Name, Directory* Parent);
	virtual std::string GetName() = 0;
	virtual std::string GetFullName() = 0;
	virtual Directory* GetParent() = 0;
};
#endif