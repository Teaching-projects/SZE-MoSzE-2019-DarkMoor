#ifndef TERMINAL_H
#define TERMINAL_H
#include <string>
#include <map>
#include "json/json.h"

class CommandBase;
class Directory;
class Terminal
{
private:
	static Terminal* terminal;

	std::map<std::string, CommandBase*> commands;
	Directory* root;
	Directory* actual;
	bool exit;
	bool stdoRedirect;
	std::string stdoPath;

	Terminal();
	Terminal(Json::Value RootValue);

	std::string Trim(std::string str);
	void StdOutWriteFile(std::string text);
	void PrintActualDir();
public:
	~Terminal();

	static Terminal* GetInstance();
	static Terminal* GetInstance(Json::Value RootValue);

	Directory* GetRoot();
	Directory* GetActual();
	void SetActual(Directory* dir);
	void MainLoop();
	void AddCommand(CommandBase* commmand);
	bool GetExit();
	void SetExit(bool exit);
	Json::Value GetFSAsJson();
	bool GetStdoRedirect();
	void SetStdoRedirect(bool b);
	void SetStdoPath(std::string path);
	void StdOut(std::string);
};
#endif