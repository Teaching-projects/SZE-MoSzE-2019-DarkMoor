#include "FSJsonHandler.h"
#include "json/json.h"
#include <iostream>
#include <fstream>
#include <string>

FSJsonHandler* FSJsonHandler::instance = nullptr;

FSJsonHandler::FSJsonHandler()
{

}

FSJsonHandler::~FSJsonHandler()
{

}

FSJsonHandler* FSJsonHandler::GetInstance()
{
	if (FSJsonHandler::instance == nullptr)
	{
		FSJsonHandler::instance = new FSJsonHandler();
	}
	return FSJsonHandler::instance;
}

Json::Value FSJsonHandler::GetRoot()
{
	return root;
}

void FSJsonHandler::SetRoot(Json::Value Root)
{
	root = Root;
}

void FSJsonHandler::ReadFile(std::string path)
{
	std::ifstream fstream(path);
	if (fstream.is_open())
	{
		try
		{
			fstream >> root;
			fstream.close();
		}
		catch (const std::exception& ex)
		{
			std::cout << ex.what() << std::endl;
		}
	}
	else
	{
		std::cout << "Failed to open this shit." << std::endl;
	}
}

void FSJsonHandler::WriteFile(std::string Path)
{
	std::ofstream file(Path);
	if (file.is_open())
	{
		try
		{
			file << root;
			file.close();
			delete& root;
		}
		catch (const std::exception& ex)
		{
			std::cout << ex.what() << std::endl;
		}
	}
	else
	{
		std::cout << "Failed to open this shit." << std::endl;
	}
}
