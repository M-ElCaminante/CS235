#ifndef TODO_LIST_H
#define TODO_LIST_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

#include "TodoListInterface.h"

class TodoList: public TodoListInterface {
public:
    std::vector <std::string> tasks;
    
    TodoList() {
       // std::cout << "In Constructor" << std::endl;
        std::ifstream infile("TODOList.txt");
        std::string line;
        
        if(infile.is_open()) {
            while(getline(infile,line)){
              // std::cout << line << '\n';
                tasks.push_back(line);
            }
            infile.close();
        }
    }
    virtual ~TodoList() {
       // std::cout <<"In Destructor" << std::endl;
        std::ofstream outfile;
        outfile.open("TODOList.txt", std::ofstream::out | std::ofstream::trunc);
        
        for(int i = 0; i < tasks.size(); i++) {
         //   std::cout << tasks[i] << '\n';
            outfile << tasks[i] << std::endl;
        }
        outfile.close();
    }
    
    /*
    *   Adds an item to the todo list with the data specified by the string "_duedate" and the task specified by "_task"
    */
    virtual void add(std::string _duedate, std::string _task) {
      // std::cout << "In add " << _duedate<< " " << _task << std::endl;
        tasks.push_back(_duedate + " " + _task);
    }

    /*
    *   Removes an item from the todo list with the specified task name
    *
    *   Returns 1 if it removes an item, 0 otherwise
    */
    virtual int remove(std::string _task) {
      //  std::cout << "In remove" << std::endl;
        for(unsigned int i = 0; i < tasks.size(); i++) {
            if (tasks[i].find(_task) != std::string::npos) {
                tasks.erase(tasks.begin() + i);
                std::cout  << "task (" << _task << ") removed" << std::endl;
                return 1;
            }
        }
        std::cout << "ERROR: (" << _task << ") not found" << std::endl;
        return 0;
    }
        
    /*
    *   Prints out the full todo list to the console
    */
    virtual void printTodoList() {
       // std::cout << "In List" << std::endl;
        if(tasks.empty()) {
            std::cout << "To-Do List is empty." << std::endl;
        }
        else {
            std::cout << "My To-Do List: " << std::endl;
            for (unsigned int i = 0; i < tasks.size(); ++i) {
                std::cout << tasks.at(i) << std::endl;
            }
        }
    }
    
    /*
    *   Prints out all items of a todo list with a particular due date (specified by _duedate)
    */
    virtual void printDaysTasks(std::string _date) {
      //  std::cout << "In Day's Tasks" << std::endl;
        for (unsigned int i = 0; i < tasks.size(); i++) {
            if (tasks[i].find(_date) != std::string::npos) {
               // std::cout  << "date (" << _date << ") found" << std::endl;
                std::cout << tasks.at(i) << std::endl;
            }
        }
    }
};

#endif