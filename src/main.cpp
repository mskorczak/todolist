#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <ctime>
#include "item.hpp"
#include "todo.hpp"

void display(TodoList todo)
{
	cout << "Todo Title: " << todo.get_todo_title() << endl;
	for(int i = 0; i < todo.get_item_count(); i++)
	{
		cout << todo.get_list()[i];
	}
	cout << endl;
}

int main()
{
	TodoList list1("list 1");
	list1.add_item("", "", time(NULL), time(NULL));
	list1.add_item("test 2", "big stinky description", time(NULL), time(NULL));
	list1.add_item("search BIG","desc", time(NULL), time(NULL));
	display(list1);
	list1.search_item("search");
	list1.search_item("test");
	list1.search_item("13:23:00");
	list1.search_item("10:41:00");
	list1.delete_item("test");
	display(list1);
	Item test = list1.get_list().at(0);
	cout << test << endl;
	test.set_item_status(true);
	cout << test << endl;
	return 0;
}

