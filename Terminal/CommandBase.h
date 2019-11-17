#ifndef COMMANDBASE_H
#define COMMANDBASE_H
#include <string>
#include <vector>

class CommandBase
{
private:
	std::string name;
protected:
	int nonOptionalParams;
	std::string options;

	virtual bool ValidateParams(std::vector<std::string> args) = 0;
public:
	CommandBase(std::string Name, std::string Options, int NonOptionalParams)
	{
		this->options = Options;
		this->nonOptionalParams = NonOptionalParams;
		this->name = Name;
	}
	std::string GetName() 
	{
		return this->name;
	}
	virtual void Execute(std::string params) = 0;
};
#endif // !COMMANDBASE_H