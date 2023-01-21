#ifndef UTILS_H
#define UTILS_H

using namespace std;

void handleAddingNewTodo(list<TodoItem> &todoItems, ostringstream &error_message);

void handleCompletingTodo(list<TodoItem> &todoItems, ostringstream &error_message);

void handleDeletingTodo(list<TodoItem> &todoItems, ostringstream &error_message);

#endif
