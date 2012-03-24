#include "Task.h"
#include <iostream>
Task::Task()
{
	time_t rawtime;
	struct tm * timeinfo;

	time ( &rawtime );
	timeinfo = localtime ( &rawtime );
	datetime = asctime (timeinfo);
	datetime[24] = ' ';
}

Task::Task(std::string tit, std::string desc, int p, int s):
  title(tit), description(desc)
{
	time_t rawtime;
	struct tm * timeinfo;

	time ( &rawtime );
	timeinfo = localtime ( &rawtime );
	datetime = asctime (timeinfo);
	datetime[24] = ' ';
	prior = static_cast<Task::priority>(p);
	sever = static_cast<Task::severity>(s);
}

Task::Task(std::string tit, std::string desc, int p, int s, std::string dt):
  title(tit), description(desc), datetime(dt)
{
  prior = static_cast<Task::priority>(p);
  sever = static_cast<Task::severity>(s);
}


int Task::getId()
{
  return id;
}

void Task::setId(int i)
{
  id = i;
}

