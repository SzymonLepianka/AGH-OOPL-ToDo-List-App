#include <iostream>
#include <string>
#include <list>
#include <ctime>

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

    const string getDescription() {
        return description;
    }

    bool isCompleted() {
        return completed;
    }

    bool create(string newDescription) {
        //generates a random integer between 1 and 100
        todoItemId = rand() % 100 + 1;
        description = newDescription;
        return true;
    }
};

int main() {
    list<TodoItem> todoItems;
    list<TodoItem>::iterator it;
    todoItems.clear();

    srand(time(NULL));

    TodoItem test;
    test.create("this is a test");
    todoItems.push_back(test);

    while (1) {
        system("cls");
        cout << "Todo List App" << endl;
        cout << endl << endl;

        for (it = todoItems.begin(); it != todoItems.end(); it++) {
            cout << it->getTodoItemId() << " , " << it->getDescription() << " , " << it->isCompleted() << endl;
        }
        break;
    }
    return 0;
}
