#ifndef FSJSONHANDLER_H
#define FSJSONHANDLER_H
#include "json/json.h"
#include <string>

class FSJsonHandler
{
private:
	static FSJsonHandler* instance;

	Json::Value root;
	FSJsonHandler();
public:
	~FSJsonHandler();
	static FSJsonHandler* GetInstance();
	void ReadFile(std::string Path);
	void WriteFile(std::string Path);
	Json::Value GetRoot();
	void SetRoot(Json::Value Root);
};
#endif // !FSJSONHANDLER

