#include <iostream>
#include <string>
#include <list>
#include <fstream>
#include <sstream>
#include "TodoItem.h"
#include "Utils.h"
#include "Globals.h"

using namespace std;


int main() {
    string input_option;
    ostringstream error_message;
    list<TodoItem> todoItems;
    todoItems = readTodoItemsFromFile("todolist.txt");

    while (true) {
        system("cls");

        cout << error_message.str() << endl;
        error_message.str("");
        error_message.clear();

        cout << "Todo List App" << endl;
        cout << endl << endl;

        printTodoItems(todoItems);

        cout << endl << endl;

        cout << "Main Menu" << endl;
        cout << "[1] Add a new Todo" << endl;
        cout << "[2] Mark Todo as complete" << endl;
        cout << "[3] Delete Todo" << endl;
        cout << "[4] Quit" << endl;
        cout << "Enter your choice: ";

        getline(cin, input_option);

        if (input_option == "1") {
            handleAddingNewTodo(todoItems, error_message);
        } else if (input_option == "2") {
            handleCompletingTodo(todoItems, error_message);
        } else if (input_option == "3") {
            handleDeletingTodo(todoItems, error_message);
        } else if (input_option == "4") {
            cout << "Quitting..." << endl;
            saveTodoItemsToFile(todoItems, "todolist.txt");
            break;
        } else {
            error_message << "Error: Invalid option selected" << endl;
        }
    }

    system("pause");
    return 0;
}
