#ifndef RM_H
#define RM_H
#include "CommandBase.h"
#include <string>
#include <vector>

class RM : public CommandBase
{
private:
	void RemoveDirectory(std::string path);

	void ResetOptions() override;
	bool SetOptions(char c) override;

	bool recursive;
	bool force;
public:
	RM(std::string Name, std::string Options, int NonOptionalParams);
	~RM();
	void Execute(std::string params) override;
};
#endif // !RM_H