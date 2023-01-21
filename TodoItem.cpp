#include "TodoItem.h"
#include <iostream>
#include <fstream>

using namespace std;

int TodoItem::nextId = 1; // initialize the static variable to 1

TodoItem::TodoItem(string _description) : description(std::move(_description)), completed(false) {
    todoItemId = nextId++;
}

TodoItem::~TodoItem() = default;

int TodoItem::getTodoItemId() const {
    return todoItemId;
}

std::string TodoItem::getDescription() {
    return description;
}

bool TodoItem::isCompleted() const {
    return completed;
}

void TodoItem::setCompleted(bool _completed) {
    completed = _completed;
}

void TodoItem::save(ofstream &file) {
    file << todoItemId << "," << description << "," << completed << endl;
}
