#ifndef TASKOPERATION_H
#define TASKOPERATION_H

#include <string>



class TaskOperation
{
	public:
		void addTask();
		void showMenu();
		void handleMenu(int decision);
		void showTasks();
		void deleteTask();
		void editTask();
		void saveFile();
		void loadFile();
		bool pinPrompt();
		bool pinLogin(std::string chkpin);
		bool changePin();
		int lastOper;
// 		
	//private:
		
};

#endif