#include "TodoItem.h"
#include <iostream>
#include <fstream>
#include <list>
#include <string>
#include <sstream>

using namespace std;

list<TodoItem> readTodoItemsFromFile(const string &fileName) {
    list<TodoItem> todoItems;
    todoItems.clear();

    // Read todos from file
    ifstream openfile(fileName);
    if (openfile.good()) {
        string line;
        while (getline(openfile, line)) {
            stringstream ss(line);
            string id;
            string description;
            string completed;

            if (!getline(ss, id, ',')) {
                cerr << "Error: Invalid format in file. Could not read TodoItem ID." << endl;
                continue;
            }

            // Validate ID
            int itemId;
            try {
                itemId = stoi(id);
            } catch (const std::invalid_argument &e) {
                cerr << "Error: Invalid TodoItem ID in file. Must be an integer." << endl;
                continue;
            }
            if (itemId < 1) {
                cerr << "Error: Invalid TodoItem ID in file. Must be greater than 0." << endl;
                continue;
            }

            if (!getline(ss, description, ',')) {
                cerr << "Error: Invalid format in file. Could not read TodoItem description." << endl;
                continue;
            }
            if (!getline(ss, completed, ',')) {
                cerr << "Error: Invalid format in file. Could not read TodoItem completion status." << endl;
                continue;
            }

            // Validate completion status
            if (completed != "0" && completed != "1") {
                cerr << "Error: Invalid completion status in file. Must be 0 or 1." << endl;
                continue;
            }

            TodoItem item(description);
            item.setCompleted(completed == "1");
            todoItems.push_back(item);
        }
        openfile.close();
    } else {
        cerr << "Error: Failed to open file for reading" << endl;
    }
    return todoItems;
}

void saveTodoItemsToFile(list<TodoItem> &todoItems, const string &fileName) {
    try {
        ofstream file(fileName);
        if (file.good()) {
            for (auto &item: todoItems) {
                item.save(file);
            }
            file.close();
        } else {
            cerr << "Error: Failed to open file for writing" << endl;
        }
    } catch (const std::ofstream::failure &e) {
        cerr << "Error: Failed to save todo list to file. Reason: " << e.what() << endl;
    }
}

void printTodoItems(list<TodoItem> &todoItems) {
    for (auto &todoItem: todoItems) {
        string completed = todoItem.isCompleted() ? "done" : "not done";
        cout << todoItem.getTodoItemId() << " , " << todoItem.getDescription() << " , " << completed << endl;
    }
    if (todoItems.empty()) {
        cout << "List is empty! Add your first todo!" << endl;
    }
}