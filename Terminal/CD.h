#ifndef CD_H
#define CD_H
#include "CommandBase.h"
#include <string>
#include <vector>

class Directory;
class CD : public CommandBase
{
private:
	Directory* GetTargetDirectory(std::string path);
	Directory* GetTargetDirectoryRecursive(std::string path, Directory* startDir);
	bool ValidateParams(std::vector<std::string> args) override;
public:
	CD(std::string Name, std::string Options, int NonOptionalParams);
	void Execute(std::string params) override;
};
#endif // !CD_H