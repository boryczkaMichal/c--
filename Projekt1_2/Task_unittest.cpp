#include<string>
#include "gtest/gtest.h"
#include "Task.h"

using namespace std;

string datetime = "Sat Mar 31 17:20:03 2012";
string title = "testowy";
string description = "opis";
priority p = high;
severity s = system_failure;
Task task(title, description, p, s);


TEST(TaskTest, CheckConstructor) {
	EXPECT_EQ("testowy", task.getTitle());
	EXPECT_EQ("opis", task.getDescription());
	EXPECT_EQ(high, task.getPriority());
	EXPECT_EQ(system_failure, task.getSeverity());
	EXPECT_EQ("Sat Mar 31 17:20:03 2012", task.getDateTime());
}

TEST(TaskTest, CheckTitle) {
	task.setTitle("testowy tytul");
	EXPECT_EQ("testowy tytul", task.getTitle());  
}

TEST(TaskTest, CheckDescription) {
	task.setDescription("testowy opis");
	EXPECT_EQ("testowy opis", task.getDescription());  
}

TEST(TaskTest, CheckPriority) {
	task.setPriority(high);
	EXPECT_EQ(high, task.getPriority());
	task.setPriority(medium);
	EXPECT_EQ(medium, task.getPriority());
	task.setPriority(low);
	EXPECT_EQ(low, task.getPriority());
	
	task.setPriority(0);
	EXPECT_EQ(high, task.getPriority());
	task.setPriority(1);
	EXPECT_EQ(medium, task.getPriority());
	task.setPriority(2);
	EXPECT_EQ(low, task.getPriority());
}

TEST(TaskTest, CheckSeverity) {
	task.setSeverity(system_failure);
	EXPECT_EQ(system_failure, task.getSeverity());
	task.setSeverity(blocker);
	EXPECT_EQ(blocker, task.getSeverity());
	task.setSeverity(walkaround);
	EXPECT_EQ(walkaround, task.getSeverity());  
	task.setSeverity(cosmetic);
	EXPECT_EQ(cosmetic, task.getSeverity());  

	task.setSeverity(0);
	EXPECT_EQ(system_failure, task.getSeverity());
	task.setSeverity(1);
	EXPECT_EQ(blocker, task.getSeverity());
	task.setSeverity(2);
	EXPECT_EQ(walkaround, task.getSeverity());  
	task.setSeverity(3);
	EXPECT_EQ(cosmetic, task.getSeverity()); 
}

TEST(TaskTest, CheckDate) {
	string date = "Sat Mar 30 15:15:52 2012";
	task.setDate(date);
	EXPECT_EQ(date, task.getDateTime());
}

TEST(TaskTest, CheckId) {
	task.setId(14);
	EXPECT_EQ(14, task.getId());  
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}