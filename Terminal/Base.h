#ifndef BASE_H
#define BASE_H
#include <string>
#include "json/json.h"
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
	virtual Json::Value Jsonify() = 0;
	virtual void UnJsonify(Json::Value SubValues) = 0;
};
#endif