#ifndef CD_H
#define CD_H
#include "CommandBase.h"
#include <string>
#include <vector>

class CD : public CommandBase
{
private:
	void SetActuallDirectory(std::string path);
	
	void ResetOptions() override;
	bool SetOptions(char c) override;
public:
	CD(std::string Name, std::string Options, int NonOptionalParams);
	void Execute(std::string params) override;
};
#endif // !CD_H