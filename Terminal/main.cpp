#include <string>
#include <sstream>
#include <iostream>
#include "Terminal.h"
#include "FSJsonHandler.h"

Terminal* terminal;

int main(int argc, char* argv[])
{
	if (argc > 1)
	{
		FSJsonHandler* jsonhandler = FSJsonHandler::GetInstance();
		jsonhandler->ReadFile(argv[1]);
		terminal = Terminal::GetInstance(jsonhandler->GetRoot());
		terminal->MainLoop();
		jsonhandler->SetRoot(terminal->GetFSAsJson());
		jsonhandler->WriteFile(argv[1]);
		delete jsonhandler;
	}
	else
	{
		terminal = Terminal::GetInstance();
		terminal->MainLoop();
	}
	delete terminal;
}