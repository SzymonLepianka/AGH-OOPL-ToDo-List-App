#ifndef GLOBALS_H
#define GLOBALS_H

using namespace std;

list <TodoItem> readTodoItemsFromFile(const string &fileName);

void saveTodoItemsToFile(list <TodoItem> &todoItems, const string &fileName);

void printTodoItems(list <TodoItem> &todoItems);

#endif
