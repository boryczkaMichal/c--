#include<string>
#include "gtest/gtest.h"
#include "TaskOperation.h"

using namespace std;

TaskOperation taskO;


TEST(TaskOperationTest, CheckPinLogin) {
	EXPECT_FALSE(taskO.pinLogin("zle"));
	EXPECT_TRUE(taskO.pinLogin("pass"));
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
