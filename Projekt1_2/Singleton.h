#ifndef SINGLETON_H
#define SINGLETON_H

#include<list>
#include<string>
#include "Task.h"

using namespace std;

class Singleton
{
	private:
		Singleton() {}
		Singleton(const Singleton &);
		Singleton& operator=(const Singleton&);
      
	public:
		static Singleton& getInstance()
		{
			//obiekt tworzony tylko raz
			static Singleton instance;
			return instance;
		}
		list<Task> taskList;
};

#endif
