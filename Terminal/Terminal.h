#ifndef TERMINAL_H
#define TERMINAL_H
#include <string>
#include <map>

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
	Terminal();

	std::string Trim(std::string str);
public:
	~Terminal();

	static Terminal* GetInstance();

	Directory* GetRoot();
	Directory* GetActual();
	void SetActual(Directory* dir);
	void MainLoop();
	void PrintActualDir();
	void AddCommand(CommandBase* commmand);
	bool GetExit();
	void SetExit(bool exit);
};
#endif