#ifndef COMMANDBASE_H
#define COMMANDBASE_H
#include <string>

class CommandBase
{
private:
	std::string name;
protected:
	virtual bool ValidateParams(std::string params) = 0;
public:
	CommandBase(std::string Name)
	{
		this->name = Name;
	}
	std::string GetName() 
	{
		return this->name;
	}
	virtual void Execute(std::string params) = 0;
};
#endif // !COMMANDBASE_H