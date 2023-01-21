#include "TodoItem.h"
#include <iostream>
#include <list>
#include <string>
#include <sstream>

using namespace std;

void handleAddingNewTodo(list<TodoItem> &todoItems, ostringstream &error_message) {
    string input_description;
    cout << "Enter todo item description: ";
    cin.clear();
    getline(cin, input_description);

    // validate input (description)
    if (input_description.empty()) {
        error_message << "Error: TodoItem description cannot be empty" << endl;
        return;
    }

    // check if description includes a comma
    size_t found = input_description.find(',');
    if (found != string::npos) {
        error_message << "Error: Todo description cannot contain a comma." << endl;
        return;
    }

    TodoItem newItem(input_description);
    todoItems.push_back(newItem);
}

void handleCompletingTodo(list<TodoItem> &todoItems, ostringstream &error_message) {
    string input_id;
    cout << "Enter Todo ID (to mark as completed): ";
    cin.clear();
    getline(cin, input_id);

    // validate input (ID)
    if (input_id.empty()) {
        error_message << "Error: TodoItem ID cannot be empty" << endl;
        return;
    }
    int itemId;
    try {
        itemId = stoi(input_id);
    } catch (const std::invalid_argument &e) {
        error_message << "Error: Invalid ID entered." << endl;
        return;
    }

    bool found = false;
    for (auto &todoItem: todoItems) {
        if (todoItem.getTodoItemId() == itemId) {
            todoItem.setCompleted(true);
            found = true;
            break;
        }
    }
    if (!found) {
        error_message << "Error: TodoItem with ID " << itemId << " not found" << endl;
    }
}

void handleDeletingTodo(list<TodoItem> &todoItems, ostringstream &error_message) {
    string input_id;
    list<TodoItem>::iterator it;
    cout << "Enter Todo ID (to delete): ";
    cin.clear();
    getline(cin, input_id);

    // Validate input (ID)
    if (input_id.empty()) {
        error_message << "Error: TodoItem ID cannot be empty" << endl;
        return;
    }
    int itemId;
    try {
        itemId = stoi(input_id);
    } catch (const std::invalid_argument &e) {
        error_message << "Error: Invalid ID entered." << endl;
        return;
    }

    bool found = false;
    for (it = todoItems.begin(); it != todoItems.end(); it++) {
        if (it->getTodoItemId() == itemId) {
            todoItems.erase(it);
            found = true;
            break;
        }
    }
    if (!found) {
        error_message << "Error: TodoItem with ID " << itemId << " not found" << endl;
    }
}
