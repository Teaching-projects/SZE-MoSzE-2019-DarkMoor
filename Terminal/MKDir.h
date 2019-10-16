#ifndef MKDIR_H
#define MKDIR_H
#include "CommandBase.h"
#include <string>

class Directory;
class MKDir : public CommandBase
{
	Directory* AddDirectory(std::string path);
	Directory* AddDirectoryRecursive(std::string path, Directory* startDir);
	virtual bool ValidateParams(std::string params) override;
public:
	MKDir(std::string Name) : CommandBase(Name) {}
	void Execute(std::string params) override;
};
#endif