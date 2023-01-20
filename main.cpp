#include <iostream>
#include <string>
#include <list>
#include <ctime>
#include <fstream>
#include <sstream>

using namespace std;

class TodoItem {
private:
    int todoItemId;
    string description;
    bool completed;
public:
    TodoItem() : todoItemId(0), description(""), completed(false) {

    }

    ~TodoItem() = default;

    int getTodoItemId() {
        return todoItemId;
    }

    void setTodoItemId(int _todoItemId) {
        todoItemId = _todoItemId;
    }

    const string getDescription() {
        return description;
    }

    bool isCompleted() {
        return completed;
    }

    void setCompleted(bool _completed) {
        completed = _completed;
    }

    bool create(string newDescription) {
        //generates a random integer between 1 and 100
        todoItemId = rand() % 100 + 1;
        description = newDescription;
        return true;
    }

    void save(ofstream &file) {
        file << todoItemId << "," << description << "," << completed << endl;
    }
};

int main() {
    char input_option;
    string input_description;
    int input_id;
    list<TodoItem> todoItems;
    list<TodoItem>::iterator it;
    todoItems.clear();

    srand(time(NULL));

    // Read todos from file
    ifstream openfile("todolist.txt");
    if (openfile.good()) {
        string line;
        while (getline(openfile, line)) {
            stringstream ss(line);
            TodoItem item;
            string id;
            string description;
            string completed;

            if (!getline(ss, id, ',')) {
                cerr << "Error: Invalid format in file. Could not read TodoItem ID." << endl;
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

            // Validate ID
            int itemId;
            try {
                itemId = stoi(id);
            } catch (const std::invalid_argument& e) {
                cerr << "Error: Invalid TodoItem ID in file. Must be an integer." << endl;
                continue;
            }
            if (itemId < 1) {
                cerr << "Error: Invalid TodoItem ID in file. Must be greater than 0." << endl;
                continue;
            }

            // Validate completion status
            if (completed != "0" && completed != "1") {
                cerr << "Error: Invalid completion status in file. Must be 0 or 1." << endl;
                continue;
            }

            item.create(description);
            item.setCompleted(completed == "1");
            item.setTodoItemId(itemId);
            todoItems.push_back(item);
        }
        openfile.close();
    } else {
        cerr << "Error: Failed to open file for reading" << endl;
    }

    while (1) {
//        system("cls");
        cout << "Todo List App" << endl;
        cout << endl << endl;

        for (it = todoItems.begin(); it != todoItems.end(); it++) {
            string completed = it->isCompleted() ? "done" : "not done";
            cout << it->getTodoItemId() << " , " << it->getDescription() << " , " << completed << endl;
        }

        if (todoItems.empty()) {
            cout << "List is empty! Add your first todo!" << endl;
        }

        cout << endl << endl;

        cout << "[a]dd a new todo" << endl;
        cout << "[c]omplete a todo" << endl;
        cout << "[q]uit" << endl;

        cout << "choice: ";
        cin >> input_option;

        if (input_option == 'q') {
            cout << "Quitting..." << endl;

            try {
                ofstream file("todolist.txt");
                if (file.good()) {

                    for (auto &todoItem: todoItems) {
                        todoItem.save(file);
                    }
                    file.close();
                } else {
                    cerr << "Error: Failed to open file for writing" << endl;
                }
            } catch (const std::ofstream::failure &e) {
                cerr << "Error: Failed to save todo list to file. Reason: " << e.what() << endl;
            }

            break;
        } else if (input_option == 'c') {
            cout << "Enter ID to mark completed: ";
            cin >> input_id;

            for (it = todoItems.begin(); it != todoItems.end(); it++) {
                if (input_id == it->getTodoItemId()) {
                    it->setCompleted(true);
                    break;
                }
            }
        } else if (input_option == 'a') {
            cout << "Add a new description: ";
            cin.clear();
            cin.ignore();
            getline(cin, input_description);
            TodoItem newItem;
            newItem.create(input_description);
            todoItems.push_back(newItem);
        }
    }

    system("pause");
    return 0;
}
