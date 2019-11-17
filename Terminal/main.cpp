#include <string>
#include <sstream>
#include <iostream>
#include "Terminal.h"

Terminal* terminal;

int main()
{
	terminal = Terminal::GetInstance();
	terminal->MainLoop();
	delete terminal;
}