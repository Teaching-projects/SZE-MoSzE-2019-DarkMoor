#ifndef CD_H
#define CD_H
#include "CommandBase.h"
#include <string>

class Directory;
class CD : public CommandBase
{
private:
	Directory* GetTargetDirectory(std::string path);
	Directory* GetTargetDirectoryRecursive(std::string path, Directory* startDir);
	virtual bool ValidateParams(std::string params) override;
public:
	CD(std::string Name) : CommandBase(Name) {}
	void Execute(std::string params) override;
};
#endif // !CD_H