#ifndef LS_H
#define LS_H
#include "CommandBase.h"
#include <string>

class Directory;
class LS : public CommandBase
{
private:
	Directory* GetDirectory(std::string path);
	Directory* GetDirectoryRecursive(std::string path, Directory* startDir);
	virtual bool ValidateParams(std::string params) override;
public:
	LS(std::string Name) : CommandBase(Name) {}
	void Execute(std::string params) override;
};
#endif