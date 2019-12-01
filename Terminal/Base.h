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
	virtual ~Base() = 0;
	virtual std::string GetName();
	virtual void SetName(std::string);
	virtual std::string GetFullName() = 0;
	virtual bool IsChildOf(Directory* dir);
	virtual Json::Value Jsonify() = 0;
	virtual void UnJsonify(Json::Value SubValues) = 0;

	virtual Directory* GetParent();
	virtual void SetParent(Directory* Parent);
};
#endif