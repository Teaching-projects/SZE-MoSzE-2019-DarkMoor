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
#include "Exit.h"


Terminal* Terminal::terminal = nullptr;
Directory* root;
Directory* actual;

Terminal::Terminal()
{
	this->root = new Directory("/", nullptr);
	this->actual = Terminal::root;
	this->exit = false;
}

Terminal::~Terminal()
{
	delete root;
	for (auto c : commands)
	{
		delete c.second;
	}
	commands.clear();
}

Terminal* Terminal::GetInstance()
{
	if (Terminal::terminal == nullptr)
	{
		Terminal::terminal = new Terminal();
		Terminal::terminal->AddCommand(new LS("ls"));
		Terminal::terminal->AddCommand(new MKDir("mkdir"));
		Terminal::terminal->AddCommand(new CD("cd"));
		Terminal::terminal->AddCommand(new Exit("exit"));
	}
	return Terminal::terminal;
}

void Terminal::PrintActualDir()
{
	std::cout << this->actual->GetFullName() << ">";
}

void Terminal::MainLoop()
{
	std::string input;
	this->PrintActualDir();
	while (!exit)
	{
		std::getline(std::cin, input);
		std::cout << std::endl;
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
		if (!exit)
		{
			this->PrintActualDir();
		}
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

bool Terminal::GetExit()
{
	return this->exit;
}

void Terminal::SetExit(bool exit)
{
	this->exit = exit;
}