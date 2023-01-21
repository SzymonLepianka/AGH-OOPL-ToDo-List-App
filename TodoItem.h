#ifndef TODOITEM_H
#define TODOITEM_H

#include <string>

class TodoItem {
private:
    int todoItemId;
    std::string description;
    bool completed;
    static int nextId; // static variable to keep track of the next ID to be assigned

public:
    explicit TodoItem(std::string _description);

    ~TodoItem();

    [[nodiscard]] int getTodoItemId() const;

    std::string getDescription();

    [[nodiscard]] bool isCompleted() const;

    void setCompleted(bool _completed);

    void save(std::ofstream &file);
};

#endif
