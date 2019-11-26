#ifndef MKDIR_H
#define MKDIR_H
#include "CommandBase.h"
#include <string>
#include <vector>

class Directory;
class MKDir : public CommandBase
{
	void AddDirectory(std::string path);
	
	void ResetOptions() override;
	bool SetOptions(char c) override;
public:
	MKDir(std::string Name, std::string Options, int NonOptionalParams);
	void Execute(std::string params) override;
};
#endif