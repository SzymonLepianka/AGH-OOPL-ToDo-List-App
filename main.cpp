#include <iostream>
#include <string>
#include <list>
#include <fstream>
#include <sstream>

using namespace std;

class TodoItem {
private:
    int todoItemId;
    string description;
    bool completed;
    static int nextId; // static variable to keep track of the next ID to be assigned

public:
    explicit TodoItem(string _description) : description(std::move(_description)), completed(false) {
        todoItemId = nextId++;
    }

    ~TodoItem() = default;

    [[nodiscard]] int getTodoItemId() const {
        return todoItemId;
    }

    string getDescription() {
        return description;
    }

    [[nodiscard]] bool isCompleted() const {
        return completed;
    }

    void setCompleted(bool _completed) {
        completed = _completed;
    }

    void save(ofstream &file) {
        file << todoItemId << "," << description << "," << completed << endl;
    }
};

int TodoItem::nextId = 1; // initialize the static variable to 1

int main() {
    string input_option, input_id, input_description;
    ostringstream error_message;
    list<TodoItem> todoItems;
    list<TodoItem>::iterator it;
    todoItems.clear();

    // Read todos from file
    ifstream openfile("todolist.txt");
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

    while (true) {
        system("cls");

        cout << error_message.str() << endl;
        error_message.str("");
        error_message.clear();

        cout << "Todo List App" << endl;
        cout << endl << endl;

        for (auto &todoItem: todoItems) {
            string completed = todoItem.isCompleted() ? "done" : "not done";
            cout << todoItem.getTodoItemId() << " , " << todoItem.getDescription() << " , " << completed << endl;
        }

        if (todoItems.empty()) {
            cout << "List is empty! Add your first todo!" << endl;
        }

        cout << endl << endl;

        cout << "Main Menu" << endl;
        cout << "[1] Add a new Todo" << endl;
        cout << "[2] Mark Todo as complete" << endl;
        cout << "[3] Delete Todo" << endl;
        cout << "[4] Quit" << endl;
        cout << "Enter your choice: ";

        getline(cin, input_option);

        if (input_option == "1") {
            cout << "Enter todo item description: ";
            cin.clear();
            getline(cin, input_description);
            if (input_description.empty()) {
                error_message << "Error: TodoItem description cannot be empty" << endl;
                continue;
            }
            TodoItem newItem(input_description);
            todoItems.push_back(newItem);
        } else if (input_option == "2") {
            cout << "Enter Todo ID (to mark as completed): ";
            cin.clear();
            getline(cin, input_id);

            // Validate input (ID)
            if (input_id.empty()) {
                error_message << "Error: TodoItem ID cannot be empty" << endl;
                continue;
            }
            int itemId;
            try {
                itemId = stoi(input_id);
            } catch (const std::invalid_argument &e) {
                error_message << "Error: Invalid ID entered." << endl;
                continue;
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
        } else if (input_option == "3") {
            cout << "Enter Todo ID (to delete): ";
            cin.clear();
            getline(cin, input_id);

            // Validate input (ID)
            if (input_id.empty()) {
                error_message << "Error: TodoItem ID cannot be empty" << endl;
                continue;
            }
            int itemId;
            try {
                itemId = stoi(input_id);
            } catch (const std::invalid_argument &e) {
                error_message << "Error: Invalid ID entered." << endl;
                continue;
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
        } else if (input_option == "4") {
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
        } else {
            error_message << "Error: Invalid option selected" << endl;
        }
    }

    system("pause");
    return 0;
}
