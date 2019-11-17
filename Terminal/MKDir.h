#ifndef MKDIR_H
#define MKDIR_H
#include "CommandBase.h"
#include <string>
#include <vector>

class Directory;
class MKDir : public CommandBase
{
	Directory* AddDirectory(std::string path);
	Directory* AddDirectoryRecursive(std::string path, Directory* startDir);
	bool ValidateParams(std::vector<std::string> args) override;
public:
	MKDir(std::string Name, std::string Options, int NonOptionalParams);
	void Execute(std::string params) override;
};
#endif