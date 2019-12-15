#include "gtest/gtest.h"
#include "../Terminal/Terminal.h"
#include "../Terminal/Directory.h"
#include "../Terminal/File.h"
#include "../Terminal/CD.h"

class CDTest : public ::testing::Test
{
protected:
	Terminal* terminal;
	CD* cd;
	virtual void SetUp()
	{
		terminal = Terminal::GetInstance();
		terminal->SetActual(terminal->GetRoot()->AddDirectory("rootsub"));
		cd = new CD("cd", "", 1);
	}

	virtual void TearDown()
	{
		delete Terminal::GetInstance();
		delete cd;
	}
};

TEST_F(CDTest, CheckCD)
{
	cd->Execute("./sdir");
	ASSERT_STREQ("rootsub", terminal->GetActual()->GetName().c_str());
	cd->Execute(".././rootsub");
	ASSERT_STREQ("rootsub", terminal->GetActual()->GetName().c_str());
	cd->Execute("./..");
	ASSERT_STREQ("/", terminal->GetActual()->GetName().c_str());
}