#include <iostream>
#include <string>
#include "Terminal.h"
#include <sstream>
#include <vector>
#include "Directory.h"
#include "CommandBase.h"
#include "CD.h"
#include "LS.h"
#include "MKDir.h"


Terminal* Terminal::terminal = nullptr;
Directory* Terminal::root;
Directory* Terminal::actual;

Terminal::~Terminal()
{
	for (auto c : commands)
	{
		delete& c.second;
	}
	commands.clear();
	delete& commands;
	delete root;
	delete actual;
	delete terminal;
}

Terminal* Terminal::GetInstance()
{
	if (Terminal::terminal == nullptr)
	{
		Terminal::terminal = new Terminal();
		Terminal::root = new Directory("/", nullptr);
		Terminal::actual = Terminal::root;
		Terminal::terminal->AddCommand(new LS("ls"));
		Terminal::terminal->AddCommand(new MKDir("mkdir"));
		Terminal::terminal->AddCommand(new CD("cd"));
	}
	return Terminal::terminal;
}

void Terminal::PrintActualDir()
{
	std::cout << this->actual->GetFullName() + ">";
}

void Terminal::MainLoop()
{
	std::string input;
	this->PrintActualDir();
	while (true)
	{
		std::getline(std::cin, input);
		std::stringstream ss(input);
		std::string element;
		if (std::getline(ss, element, ' '))
		{
			for (auto c : commands)
			{
				if (c.first == element)
				{
					element = "";
					std::getline(ss, element, ' ');
					c.second->Execute(element);
				}
			}
		}
		this->PrintActualDir();
	}
}

void Terminal::AddCommand(CommandBase* command)
{
	commands.insert(std::pair<std::string, CommandBase*>(command->GetName(), command));
}

Directory* Terminal::GetRoot()
{
	return Terminal::root;
}

Directory* Terminal::GetActual()
{
	return Terminal::actual;
}

void Terminal::SetActual(Directory* dir)
{
	Terminal::actual = dir;
}