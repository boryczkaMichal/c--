#include "Task.h"
#include "TaskOperation.h"
#include "Singleton.h"

#include <iostream>
#include <iomanip>
#include <list>
#include <cstdlib>
#include<time.h>
#include <limits>
#include <fstream>
#include <sstream>

using namespace std;

ostream& operator<< ( ostream& out, const Task::priority& x )
{
	switch ( x ) {	  
	  case 0: out<<"high"; break;
	  case 1: out<<"medium"; break;
	  case 2: out<<"low"; break;
	}
	return out;
}

ostream& operator<< ( ostream& out, const Task::severity& x )
{
	switch ( x ) {
	  case 0: out<<"system failure"; break;
	  case 1: out<<"blocker"; break;
	  case 2: out<<"walkaround"; break;
	  case 3: out<<"cosmetic"; break;
	}
	return out;
}

void TaskOperation::addTask()
{
 
  //Task newTask;
  int pr, sr;
  string title, description;
  cout << "Podaj tytul nowego zadania:\n";
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  getline (cin,title);
  cout << "Podaj opis:\n";
  getline (cin,description);
  cout << "Wybierz priorytet:\n0. high\n1. medium\n2. low\n";  
  cin >> pr;
  //newTask.setPriority(static_cast<Task::priority>(pr));
  cout << "Wybierz severity:\n0. system failure\n1. blocker\n2. walkaround\n3. cosmetic\n";  
  cin >> sr;
  //newTask.setSeverity(static_cast<Task::severity>(sr)); 
  Singleton::getInstance().taskList.push_back( Task(title, description, pr, sr) );
  cout << "\nNowy element dodany!" << endl;

}

void TaskOperation::showMenu()
{
	cout << "+-----------+\n";
	cout << "| TODO List |\n";
	cout << "+-----------+\n";
	cout << "\n";
	cout << "Menu główne:\n";
	cout << "1. Wyświetl listę\n";
	cout << "2. Dodaj element\n";
	cout << "3. Usuń element\n";
	cout << "4. Zapisz do pliku\n";
	cout << "5. Wczytaj z pliku\n";
	cout << "6. Zmień hasło\n";
	cout << "7. Wyjście\n";
	cout << "\n";
	cout << "Twój wybór: ";
}

void TaskOperation::handleMenu(int decision)
{
	cout << "\n";
	switch(decision){
	
	case 1:
		showTasks();
		lastOper = 1;
		break;
	case 2:
		addTask();
		lastOper = 2;
		break;
	case 3:
		if(lastOper != 1)
		  showTasks();
		deleteTask();
		lastOper = 3;
		break;
	case 4:
		saveFile();
		lastOper = 5;
		break;
	case 5:
		loadFile();
		lastOper = 6;
		break;
	case 6:
		changePin();
		lastOper = 9;
		break;
	case 7:
		cout << "Koniec programu!" << endl;
		exit(0);
	}
	
}

void TaskOperation::showTasks()
{
	int id=0;
	cout << "+---+------------------------+----------------------+-----------------------+---------+--------------+" << endl;
	cout << " " << left << setw(4) << "id" << setw(25) << "data dodania" << setw(24) << "tytuł" << setw(24) << "opis" << setw(10) << "priorytet" << setw(14) << "severity" << endl;
	cout << "+---+------------------------+----------------------+-----------------------+---------+--------------+" << endl;
	for( list<Task>::iterator iter=Singleton::getInstance().taskList.begin(); iter != Singleton::getInstance().taskList.end(); ++iter,id++ ){
	  (*iter).setId(id);
	  /*
	  cout << "---------------------------------------" << endl;
	  cout << "id: " << id << endl;
	  cout << "data dodania: " << (*iter).datetime;
	  cout << "tytuł: " << (*iter).title << endl;  
	  cout << "opis: " << (*iter).description << endl;
	  cout << "priorytet: " << (*iter).prior << endl;
	  cout << "severity: " << (*iter).sever << endl;
	  cout << "---------------------------------------" << endl << endl;
	  */
	  
	  cout << " " << setw(4) << id << setw(25) << (*iter).getDateTime() << setw(23) << (*iter).getTitle() << setw(24) << (*iter).getDescription() << setw(10) << (*iter).getPriority() << setw(14) << (*iter).getSeverity() << endl;
	}
	cout << "+---+------------------------+----------------------+-----------------------+---------+--------------+" << endl;
}

void TaskOperation::deleteTask()
{
	int tempDelId;
	cout << "Podaj id elementu do usunięcia:\n";
	cin >> tempDelId;
	for( list<Task>::iterator iter=Singleton::getInstance().taskList.begin(); iter != Singleton::getInstance().taskList.end(); ++iter){
	  if ((*iter).getId() == tempDelId){
	    Singleton::getInstance().taskList.erase(iter);
	    break;
	  }
	}
	cout << "\nElement usunięty!" << endl;
}

void TaskOperation::editTask()
{
	int tempId;
	cout << "Podaj id elementu do edycji:\n";
	cin >> tempId;
	for( list<Task>::iterator iter=Singleton::getInstance().taskList.begin(); iter != Singleton::getInstance().taskList.end(); ++iter){
	  if ((*iter).getId() == tempId){
	    int temp;
	    string dummy;
	    cout << "Podaj nowy tytul zadania:\n";
	    cin.ignore(numeric_limits<streamsize>::max(), '\n');
	    getline (cin,dummy);
	    (*iter).setTitle(dummy);
	    cout << "Podaj nowy opis:\n";
	    getline (cin,dummy);
	    (*iter).setDescription(dummy);
	    cout << "Wybierz priorytet:\n0. high\n1. medium\n2. low\n";  
	    cin >> temp;
	    (*iter).setPriority(static_cast<Task::priority>(temp));
	    cout << "Wybierz severity:\n0. system failure\n1. blocker\n2. walkaround\n3. cosmetic\n";  
	    cin >> temp;
	    (*iter).setSeverity(static_cast<Task::severity>(temp));
	    break;
	  }
	}
	cout << "\nElement zmieniony!" << endl;
}

bool TaskOperation::pinPrompt() {
  cout << "Podaj hasło: ";
  string chkpin;
  cin >> chkpin;
  return pinLogin(chkpin);
}

bool TaskOperation::pinLogin(string chkpin) {
  string pin;
  ifstream pinfile ("pwd");
  if (pinfile.is_open())
    getline (pinfile,pin);  
  pinfile.close();
  if (!pin.compare(chkpin))
     return true;
  else {
     cout << "Błędne hasło!" << endl;
     return false;
  }  
}

bool TaskOperation::changePin() {
  if(pinPrompt()){
    string newpin;
    cout << "Podaj nowe hasło: ";
    cin >> newpin;
    fstream pinfile;
    pinfile.open("pwd", ios::in | ios::out | ios::trunc);
    if (pinfile.good()){
      pinfile << newpin << endl; 
      cout << endl << "Hasło zmienione" << endl;
    }
    pinfile.close();
  }
}

void TaskOperation::saveFile() {
  fstream file;
  file.open("backup.txt", ios::in | ios::out | ios::trunc);
  if(file.good()) {
	int id=0;
	/*
	file << "+---+------------------------+----------------------+-----------------------+---------+--------------+" << endl;
	file << " " << left << setw(4) << "id" << setw(25) << "data dodania" << setw(24) << "tytuł" << setw(24) << "opis" << setw(10) << "priorytet" << setw(14) << "severity" << endl;
	file << "+---+------------------------+----------------------+-----------------------+---------+--------------+" << endl;
	*/
	 for( list<Task>::iterator iter=Singleton::getInstance().taskList.begin(); iter != Singleton::getInstance().taskList.end(); ++iter,id++ ){
	  (*iter).setId(id);
	  
	  file << id << endl;
	  file << (*iter).getDateTime() <<endl;
	  file << (*iter).getTitle() << endl;  
	  file << (*iter).getDescription() << endl;
	  file << (*iter).getPriority() << endl;
	  file << (*iter).getSeverity() << endl;
	  file << "---------------------------------------" << endl;
	  
	  
	  //file << " " << setw(4) << id << setw(25) << (*iter).datetime << setw(23) << (*iter).title << setw(24) << (*iter).description << setw(10) << (*iter).prior << setw(14) << (*iter).sever << endl;
	}
	//file << "+---+------------------------+----------------------+-----------------------+---------+--------------+" << endl;
	
	cout << "\nDane zapisane!" << endl;
  }
  file.close();
}

void TaskOperation::loadFile() {
  ifstream myfile ("backup.txt");
  if (myfile.is_open())
  {
    while ( myfile.good() )
    {
      string datetime, title, description, pr, sr;
      int id2, pri, ser;
      getline (myfile,pr);
      istringstream iss( pr );
      iss >> id2;
      //newTask.setId(id2);
      getline (myfile,datetime);
      getline (myfile,title);
      getline (myfile,description);
      
      getline (myfile,pr );
      cout << pr << endl;
      if(!pr.compare("high")){
	pri = 0;
	//newTask.setPriority(static_cast<Task::priority>(0));
      }
      else if(!pr.compare("medium")){
	pri = 1;
	//newTask.setPriority(static_cast<Task::priority>(1));
      }
      else if(!pr.compare("low")){
	pri = 2;
	//newTask.setPriority(static_cast<Task::priority>(2));
      }

      getline (myfile,sr );
      cout << sr << endl;
      if(!sr.compare("system failure")){
	ser = 0;
	//newTask.setSeverity(static_cast<Task::severity>(0));
      }
      else if(!sr.compare("blocker")){
	ser = 1;
	//newTask.setSeverity(static_cast<Task::severity>(1));
      }
      else if(!sr.compare("walkaround")){
	ser = 2;
	//newTask.setSeverity(static_cast<Task::severity>(2));
      }
      else if(!sr.compare("cosmetic")){
	ser = 3;
	//newTask.setSeverity(static_cast<Task::severity>(3));
      }
      
      getline (myfile,pr);
      cout << pr << endl;
      if(myfile.eof())
	break;
      else
	Singleton::getInstance().taskList.push_back( Task(title, description, pri, ser, datetime) );
    }
    myfile.close();
    cout << "\nDane wczytane!" << endl;
  }

  
}
