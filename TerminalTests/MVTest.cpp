#include "gtest/gtest.h"
#include "../Terminal/Terminal.h"
#include "../Terminal/Directory.h"
#include "../Terminal/File.h"
#include "../Terminal/MV.h"

class MVTest : public ::testing::Test
{
protected:
	Terminal* terminal;
	MV* mv;
	virtual void SetUp()
	{
		terminal = Terminal::GetInstance();
		terminal->SetActual(terminal->GetRoot()->AddDirectory("rootsub"));
		terminal->GetActual()->AddDirectory("rootsubsub");
		mv = new MV("mv", "", 2);
	}

	virtual void TearDown()
	{
		delete Terminal::GetInstance();
		delete mv;
	}
};

TEST_F(MVTest, CheckMV)
{
	mv->Execute("./rootsubsub ../../");
	Base* dir = terminal->GetRoot()->GetSubelement("rootsubsub");
	ASSERT_NE(nullptr, dir);
	terminal->SetActual(dynamic_cast<Directory*>(dir));
	mv->Execute("../rootsub ../rootsubsub");
	dir = terminal->GetActual()->GetSubelement("rootsub");
	ASSERT_NE(nullptr, dir);
	mv->Execute(". ./rootsub");
	dir = terminal->GetRoot()->GetSubelement("rootsubsub");
	ASSERT_NE(nullptr, dir);
}