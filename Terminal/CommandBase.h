#ifndef COMMANDBASE_H
#define COMMANDBASE_H
#include <string>
#include <vector>

class Directory;
class CommandBase
{
private:
	std::string name;
protected:
	int nonOptionalParams;
	std::string options;

	std::string Trim(std::string str);
	std::vector<std::string> GetArgs(std::string params);
	std::vector<std::string> RemoveOptions(std::vector<std::string> params);
	bool ValidateParams(std::vector<std::string> args);

	virtual void ResetOptions() = 0;
	virtual bool SetOptions(char c) = 0;
public:
	static Directory* GetStartDirectory(std::string& path);
	static std::vector<std::string> SplitPath(std::string path);

	CommandBase(std::string Name, std::string Options, int NonOptionalParams);
	virtual ~CommandBase() = 0;
	std::string GetName();

	virtual void Execute(std::string params) = 0;
};
#endif // !COMMANDBASE_H