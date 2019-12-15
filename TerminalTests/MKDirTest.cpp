#include "gtest/gtest.h"
#include "../Terminal/Terminal.h"
#include "../Terminal/Directory.h"
#include "../Terminal/MKDir.h"

class MKDirTest : public ::testing::Test
{
protected:
	Terminal* terminal;
	MKDir* mkdir;
	virtual void SetUp()
	{
		terminal = Terminal::GetInstance();
		terminal->SetActual(terminal->GetRoot()->AddDirectory("rootsub"));
		mkdir = new MKDir("mkdir", "", 1);
	}

	virtual void TearDown()
	{
		delete Terminal::GetInstance();
		delete mkdir;
	}
};

TEST_F(MKDirTest, CheckMKDirLocal)
{
	mkdir->Execute("dir");
	Base* dir = terminal->GetActual()->GetSubelement("dir");
	ASSERT_NE(nullptr, dir);
	ASSERT_NE(nullptr, dynamic_cast<Directory*>(dir));
	dir = terminal->GetRoot()->GetSubelement("dir");
	ASSERT_EQ(nullptr, dir);
}
TEST_F(MKDirTest, CheckMKDirAbsolute)
{
	mkdir->Execute("/dir/sdir");
	Base* dir = terminal->GetRoot()->GetSubelement("dir");
	ASSERT_EQ(nullptr, dir);
	dir = terminal->GetRoot()->GetSubelement("sdir");
	ASSERT_EQ(nullptr, dir);
	dir = terminal->GetActual()->GetSubelement("sdir");
	ASSERT_EQ(nullptr, dir);
	mkdir->Execute("/rootsub/sdir");
	dir = terminal->GetActual()->GetSubelement("sdir");
	ASSERT_NE(nullptr, dir);
	ASSERT_NE(nullptr, dynamic_cast<Directory*>(dir));

}
TEST_F(MKDirTest, CheckMKDirRelative)
{
	mkdir->Execute("../dir");
	Base* dir = terminal->GetRoot()->GetSubelement("dir");
	ASSERT_NE(nullptr, dir);
	ASSERT_NE(nullptr, dynamic_cast<Directory*>(dir));
	mkdir->Execute(".././rootsub/dir");
	dir = terminal->GetActual()->GetSubelement("dir");
	ASSERT_NE(nullptr, dir);
	ASSERT_NE(nullptr, dynamic_cast<Directory*>(dir));
}