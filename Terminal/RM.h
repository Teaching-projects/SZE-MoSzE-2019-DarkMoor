#ifndef RM_H
#define RM_H
#include "CommandBase.h"
#include <string>
#include <vector>

class Base;
class RM : public CommandBase
{
private:
	Base* GetTarget(std::string path);
	Base* GetTargetRecursive(std::string path, Base* startDir);
	bool ValidateParams(std::vector<std::string> args) override;
	std::vector<std::string> GetArgs(std::string params);
	void SetOptions(char c);
	void SetForce(char c);
	void SetRecursive(char c);
	void ResetOptions();

	bool recursive;
	bool force;
public:
	RM(std::string Name, std::string Options, int NonOptionalParams);
	~RM();
	void Execute(std::string params) override;
};
#endif // !RM_H