#include "gtest/gtest.h"
#include "../Terminal/Terminal.h"
#include "../Terminal/Directory.h"

class TerminalTest : public ::testing::Test
{
protected:
	virtual void SetUp()
	{
	}

	virtual void TearDown()
	{
		delete Terminal::GetInstance();
	}
};

TEST_F(TerminalTest, CheckInitialDirectories)
{
	Terminal* terminal = Terminal::GetInstance();
	ASSERT_STREQ("/", terminal->GetRoot()->GetName().c_str());
	EXPECT_EQ(terminal->GetRoot(), terminal->GetActual());
}