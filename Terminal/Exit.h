#ifndef EXIT_H
#define EXIT_H
#include "CommandBase.h"
#include <string>

class Exit : public CommandBase
{
private:
	virtual bool ValidateParams(std::string params) override;
public:
	Exit(std::string Name) : CommandBase(Name) {}
	void Execute(std::string params) override;
};
#endif