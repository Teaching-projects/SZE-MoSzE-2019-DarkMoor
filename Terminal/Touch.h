#ifndef TOUCH_H
#define TOUCH_H
#include "CommandBase.h"
#include <string>

class File;
class Base;
class Touch : public CommandBase
{
private:
	File* AddFile(std::string path);
	File* AddFileRecursive(std::string path, Base* startDir);

	void ResetOptions() override;
	bool SetOptions(char c) override;
public:
	Touch(std::string Name, std::string Options, int NonOptionalParams);
	void Execute(std::string params) override;
};
#endif

