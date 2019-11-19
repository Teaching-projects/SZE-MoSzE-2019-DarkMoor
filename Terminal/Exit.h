#ifndef EXIT_H
#define EXIT_H
#include "CommandBase.h"
#include <string>
#include <vector>

class Exit : public CommandBase
{
private:
	void ResetOptions() override;
	bool SetOptions(char c) override;
public:
	Exit(std::string Name, std::string Options, int NonOptionalParams);
	void Execute(std::string params) override;
};
#endif