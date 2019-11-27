#ifndef MV_H
#define MV_H
#include "CommandBase.h"

class Base;
class MV : public CommandBase
{
private:
	void MoveElement(std::string source, std::string target);
	Base* GetSource(std::string path);
	Base* GetTarget(std::string path);
	void ResetOptions() override;
	bool SetOptions(char c) override;
public:
	MV(std::string Name, std::string Options, int NonOptionalParams);
	~MV();
	void Execute(std::string params) override;
};

#endif // !MV_H
