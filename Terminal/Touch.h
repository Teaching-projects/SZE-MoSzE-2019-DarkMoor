#ifndef TOUCH_H
#define TOUCH_H
#include "CommandBase.h"
#include <string>

class Touch : public CommandBase
{
private:
	void AddFile(std::string path);

	void ResetOptions() override;
	bool SetOptions(char c) override;
public:
	Touch(std::string Name, std::string Options, int NonOptionalParams);
	void Execute(std::string params) override;
};
#endif

