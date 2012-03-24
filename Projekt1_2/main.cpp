#include <list>
#include <iostream>
#include <cstddef>
#include <string>
#include <time.h>

#include "Task.h"
#include "TaskOperation.h"
#include "Singleton.h"
 
using namespace std;


 
int main()
{	
	TaskOperation taskO;
	int decision;
	if (taskO.pinPrompt()){
	  while(true){
		  taskO.showMenu();
		  cin >> decision;
		  taskO.handleMenu(decision);
	  }
	}

   return 0;
}
