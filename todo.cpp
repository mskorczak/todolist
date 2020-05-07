#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <ctime>
#include "item.cpp"

using namespace std;

class TodoList
{
	public:
		TodoList(string title);
		void add_item(string title, string desc, time_t set, time_t due);
		int get_item_count() const;
		vector<Item> get_list() const;
		string get_todo_title() const;
	private:
		vector<Item> todo_list;
		string todo_title;
		int total_item_count;
};

//todo list methods

TodoList::TodoList(string title)
{
	todo_title = title;
	total_item_count = 0;
}

void TodoList::add_item(string title, string desc, time_t set, time_t due)
{
	total_item_count++;
	// perform checks on parameters to send nulls
	if(title.empty())
	{
		title = "Untitled " + to_string(total_item_count);
	}
	if(desc.empty())
	{
		desc = "No description given.";
	}
	Item add(total_item_count, title, desc, set, due);
	todo_list.push_back(add);
}

vector<Item> TodoList::get_list() const
{
	return todo_list;
}

int TodoList::get_item_count() const
{
	return todo_list.size();
}

string TodoList::get_todo_title() const
{
	return todo_title;
}

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
	display(list1);
	return 0;
}

