#ifndef TASK_H
#define TASK_H

#include <string>

class Task
{
	public:
	  
		enum priority { high, medium, low };
		enum severity { system_failure, blocker, walkaround, cosmetic };
		
		Task();
		Task(std::string tit, std::string desc, int p, int s);
		Task(std::string tit, std::string desc, int p, int s, std::string dt);
		
		int getId();
		void setId(int id);
	
		priority getPriority()  { return prior; }
		void setPriority(priority pr)  { prior = pr; }
		void setPriority(int pr)  { prior = static_cast<Task::priority>(pr); }
		severity getSeverity()  { return sever; }
		void setSeverity(severity sr)  {  sever = sr; }
		void setSeverity(int sr)  {  sever = static_cast<Task::severity>(sr); }
		
		void setDescription(std::string desc)  { description = desc; }
		std::string getDescription()  { return description; }
		void setTitle(std::string tit)  { title = tit; }
		std::string getTitle()  { return title; }
		void setDateTime(std::string dt)  { datetime = dt; }
		std::string getDateTime()  { return datetime; }
		std::string datetime;
		
	private:
	  	int id;
		priority prior;
		severity sever;
		std::string description, title;
};

#endif