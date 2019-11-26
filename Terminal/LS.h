#ifndef LS_H
#define LS_H
#include "CommandBase.h"
#include <string>
#include <vector>

class LS : public CommandBase
{
private:
	void GetDirectory(std::string path);

	void ResetOptions() override;
	bool SetOptions(char c) override;
public:
	LS(std::string Name, std::string Options, int NonOptionalParams);
	void Execute(std::string params) override;
};
#endif