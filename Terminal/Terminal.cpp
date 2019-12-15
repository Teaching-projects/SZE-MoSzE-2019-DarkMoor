#include <iostream>
#include <string>
#include "Terminal.h"
#include <sstream>
#include <vector>
#include "Base.h"
#include "Directory.h"
#include "File.h"
#include "CommandBase.h"
#include "CD.h"
#include "LS.h"
#include "MKDir.h"
#include "Exit.h"
#include "RM.h"
#include "Touch.h"
#include "json/json.h"
#include "Echo.h"
#include "MV.h"


Terminal* Terminal::terminal = nullptr;
Directory* root;
Directory* actual;

Terminal::Terminal()
{
	this->root = new Directory("/", nullptr);
	this->actual = Terminal::root;
	this->exit = false;
	this->stdoRedirect = false;
}

Terminal::Terminal(Json::Value RootValue)
{
	if (RootValue.isMember("name") && RootValue.isMember("type"))
	{
		if (RootValue["type"].asString() == "directory")
		{
			this->root = new Directory(RootValue["name"].asString(), nullptr);
			if (RootValue.isMember("subelements"))
			{
				root->UnJsonify(RootValue["subelements"]);
			}
		}
		else
		{
			std::cout << "UnJsonify error at: root" << std::endl;
			this->root = new Directory("/", nullptr);
		}
	}
	else
	{
		std::cout << "UnJsonify error at: root" << std::endl;
		this->root = new Directory("/", nullptr);
	}
	this->actual = Terminal::root;
	this->exit = false;
	this->stdoRedirect = false;
}

Terminal::~Terminal()
{
	delete root;
	for (auto c : commands)
	{
		delete c.second;
	}
	commands.clear();
	Terminal::terminal = nullptr;
}

Terminal* Terminal::GetInstance()
{
	if (Terminal::terminal == nullptr)
	{
		Terminal::terminal = new Terminal();
		Terminal::terminal->AddCommand(new LS("ls", "", 0));
		Terminal::terminal->AddCommand(new MKDir("mkdir", "", 1));
		Terminal::terminal->AddCommand(new CD("cd", "", 1));
		Terminal::terminal->AddCommand(new Exit("exit", "", 0));
		Terminal::terminal->AddCommand(new RM("rm", "rf", 1));
		Terminal::terminal->AddCommand(new Touch("touch", "", 1));
		Terminal::terminal->AddCommand(new Echo("echo", "", 0));
		Terminal::terminal->AddCommand(new MV("mv", "", 2));
	}
	return Terminal::terminal;
}

Terminal* Terminal::GetInstance(Json::Value RootValue)
{
	if (Terminal::terminal == nullptr)
	{
		Terminal::terminal = new Terminal(RootValue);
		Terminal::terminal->AddCommand(new LS("ls", "", 0));
		Terminal::terminal->AddCommand(new MKDir("mkdir", "", 1));
		Terminal::terminal->AddCommand(new CD("cd", "", 1));
		Terminal::terminal->AddCommand(new Exit("exit", "", 0));
		Terminal::terminal->AddCommand(new RM("rm", "rf", 1));
		Terminal::terminal->AddCommand(new Touch("touch", "", 1));
		Terminal::terminal->AddCommand(new Echo("echo", "", 0));
		Terminal::terminal->AddCommand(new MV("mv", "", 2));
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
	while (!exit)
	{
		std::getline(std::cin, input);
		input = Trim(input);
		std::stringstream ss(input);
		std::string element;
		std::cout << std::endl;
		if (std::getline(ss, element, ' ') )
		{
			for (auto c : commands)
			{
				if (c.first == element)
				{
					element = "";
					std::getline(ss, element, ' ');
					c.second->Execute(Trim(input.substr(c.first.length())));
					break;
				}
			}
		}
		stdoRedirect = false;
		stdoPath = "";
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

bool Terminal::GetStdoRedirect()
{
	return this->stdoRedirect;
}

void Terminal::SetStdoRedirect(bool b)
{
	this->stdoRedirect = b;
}

void Terminal::SetStdoPath(std::string path)
{
	stdoPath = path;
}

void Terminal::StdOut(std::string text)
{
	if (this->stdoRedirect)
	{
		StdOutWriteFile(text);
	}
	else
	{
		std::cout << text << std::endl;
	}
}

void Terminal::StdOutWriteFile(std::string text)
{
	std::string originalpath = this->stdoPath;
	Base* b = nullptr;
	Directory* dir = CommandBase::GetStartDirectory(this->stdoPath);
	if (dir == nullptr)
	{
		std::cout << originalpath + ": No such file or directory" << std::endl;
		return;
	}
	std::vector<std::string> dirnames = CommandBase::SplitPath(this->stdoPath);
	unsigned int i = 1;
	for (auto t : dirnames)
	{
		if (i == dirnames.size())
		{
			File* f = nullptr;
			b = dir->GetSubelement(t);
			if (b == nullptr)
			{
				f = dir->AddFile(t);
				f->SetContent(text);
			}
			else
			{
				f = dynamic_cast<File*>(b);
				if (f != nullptr) f->SetContent(text);
			}
			return;
		}
		b = dir->GetSubelement(t);
		if (b == nullptr)
		{
			std::cout << originalpath + ": No such file or directory" << std::endl;
			return;
		}
		dir = dynamic_cast<Directory*>(b);
		if (dir == nullptr)
		{
			std::cout << originalpath + ": Not a directory" << std::endl;
			return;
		}
		i++;
	}
}

Json::Value Terminal::GetFSAsJson()
{
	return this->root->Jsonify();
}

std::string Terminal::Trim(std::string str)
{
	std::string chars = "\t\n\v\f\r ";
	str.erase(0, str.find_first_not_of(chars));
	str.erase(str.find_last_not_of(chars) + 1);
	return str;
}
