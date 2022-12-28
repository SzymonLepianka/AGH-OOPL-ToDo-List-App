#include <iostream>
#include <string>
#include <list>

using namespace std;

class ToDoItem {
private:
    int toDoItemId;
    string description;
    bool completed;
public:
    ToDoItem(): toDoItemId(0), description(""), completed(false) {

    }
    ~ToDoItem() = default;
};

int main() {
    list<ToDoItem> toDoItems;
    toDoItems.clear();

    while (1) {
        system("cls");
        cout << "ToDo List App" << endl;
        cout << endl << endl;
        


    }

    return 0;
}
