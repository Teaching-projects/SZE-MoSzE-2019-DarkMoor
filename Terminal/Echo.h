#ifndef ECHO_H
#define ECHO_H
#include "CommandBase.h"
#include <string>
#include <vector>

class Echo : public CommandBase
{
private:
	
	void ResetOptions() override;
	bool SetOptions(char c) override;
public:
	Echo(std::string Name, std::string Options, int NonOptionalParams);
	void Execute(std::string params) override;
};

#endif