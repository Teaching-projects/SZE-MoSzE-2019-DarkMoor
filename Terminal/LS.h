#ifndef LS_H
#define LS_H
#include "CommandBase.h"
#include <string>
#include <vector>

class Base;
class LS : public CommandBase
{
private:
	Base* GetDirectory(std::string path);
	Base* GetDirectoryRecursive(std::string path, Base* startDir);

	void ResetOptions() override;
	bool SetOptions(char c) override;
public:
	LS(std::string Name, std::string Options, int NonOptionalParams);
	void Execute(std::string params) override;
};
#endif