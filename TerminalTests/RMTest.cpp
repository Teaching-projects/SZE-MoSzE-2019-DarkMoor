#include "gtest/gtest.h"
#include "../Terminal/Terminal.h"
#include "../Terminal/Directory.h"
#include "../Terminal/File.h"
#include "../Terminal/RM.h"

class RMTest : public ::testing::Test
{
protected:
	Terminal* terminal;
	RM* rm;
	virtual void SetUp()
	{
		terminal = Terminal::GetInstance();
		terminal->SetActual(terminal->GetRoot()->AddDirectory("rootsub"));
		terminal->GetActual()->AddDirectory("rootsubsub");
		rm= new RM("rm", "", 1);
	}

	virtual void TearDown()
	{
		delete Terminal::GetInstance();
		delete rm;
	}
};

TEST_F(RMTest, CheckRM)
{
	rm->Execute(". -r");
	ASSERT_NE(nullptr, terminal->GetRoot()->GetSubelement("rootsub"));
	rm->Execute(".././rootsub/rootsubsub");
	ASSERT_NE(nullptr, terminal->GetActual()->GetSubelement("rootsubsub"));
	rm->Execute(".././rootsub/rootsubsub -r");
	Base* valami = terminal->GetActual()->GetSubelement("rootsubsub");
	EXPECT_TRUE(nullptr == valami);
	rm->Execute("./.. -r");
	ASSERT_NE(nullptr, terminal->GetRoot());
}