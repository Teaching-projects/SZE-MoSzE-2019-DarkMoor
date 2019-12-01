#include "gtest/gtest.h"
#include "../Terminal/Terminal.h"
#include "../Terminal/Directory.h"
#include "../Terminal/File.h"

class DirectoryTest : public ::testing::Test
{
protected:
	Directory* dir;
	Directory* c_dir;
	Directory* c_dir2;
	virtual void SetUp()
	{
		dir = new Directory("test", nullptr);
		c_dir = dir->AddDirectory("c_test");
		c_dir2 = dir->AddDirectory("c_test2");
	}

	virtual void TearDown()
	{
		delete dir;
	}
};

TEST_F(DirectoryTest, CheckAddDirectory)
{
	ASSERT_NE(nullptr, c_dir);
	ASSERT_EQ(dir, c_dir->GetParent());
	ASSERT_EQ(nullptr, dir->AddDirectory("c_test"));
}

TEST_F(DirectoryTest, CheckGetSubelement)
{
	ASSERT_EQ(c_dir, dir->GetSubelement("c_test"));
}

TEST_F(DirectoryTest, CheckRemoveDirectory)
{
	ASSERT_EQ(true, dir->RemoveSubelement("c_test"));
	ASSERT_EQ(false, dir->RemoveSubelement("c_test"));
	ASSERT_EQ(true, dir->RemoveSubelement("c_test2", false));
	ASSERT_EQ(false, dir->RemoveSubelement("c_test2", false));
}