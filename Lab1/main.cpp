#include <iostream>
#include <fstream>
#include <string>

#include "TodoList.h"

int main(int argc, char *argv[]) {
    TodoList mylist;
    for(int i = 0; i < argc; i++) {
        std::cout << "argv[" << i << "}=" << argv[i] << std::endl;
    }
    std::string firstarg = argv[1];
    if(firstarg.compare("add") == 0) {
        std::cout << "Doing an add" << std::endl;
        std::string date = argv[2];
        std::string task = argv[3];
        std::cout << "Day: " << date << " Task: " << task << std::endl;
        mylist.add(date, task);
    }
    if(firstarg.compare("remove") == 0) {
        std::cout << "removing task" << std::endl;
        std::string task = argv[2];
        std::cout << "Task: " << task << std::endl;
        mylist.remove(task);
    }
    if(firstarg.compare("printlist") == 0) {
        std::cout << "printing todolist" << std::endl;
        mylist.printTodoList();
    }
    if(firstarg.compare("printday") == 0) {
        std::string date = argv[2];
        std::cout << "printing " << date << "'s tasklist" <<std::endl;
        mylist.printDaysTasks(date);
    }
    
    return 0;
}


