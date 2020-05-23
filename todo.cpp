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
		void delete_item(string search_term);
		void delete_item(vector<int> ids);
		void delete_item(int id);
		void swap_list(vector<Item> new_list);
		int get_item_count() const;
		vector<Item> get_list() const;
		string get_todo_title() const;
		vector<int> search_item(string search_term) const;
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

void TodoList::swap_list(vector<Item> new_list)
{
	todo_list = new_list;
}

vector<int> TodoList::search_item(string search_term) const
{
	vector<int> found;
	for(int i = 0; i < get_item_count(); i++)
	{
		//check title and description
		if(get_list()[i].get_item_title().find(search_term) != string::npos || get_list()[i].get_item_title().find(search_term) != string::npos)
		{
			//cout << get_list()[i] << " search_term: " << search_term << endl;
			found.push_back(get_list()[i].get_item_id());
		}
		//check time
		//assumes that time will be given as HH:MM:SS
		if(search_term.find(":") != string::npos) {
			size_t prev = 0, pos = 0;
			vector<int> tokens;
			do{
				pos = search_term.find(":",prev);
				if(pos == string::npos) pos = search_term.length();
				string token = search_term.substr(prev,pos-prev);
				if(!token.empty()){
					tokens.push_back(stoi(token));
				}
				prev = pos + 1;
			} while (pos < search_term.length() && prev < search_term.length());
			// get set and due date and have
			time_t set = get_list()[i].get_item_time_set();
			time_t due = get_list()[i].get_item_time_due();
			tm *tm_set = localtime(&set);
			tm *tm_due = localtime(&set);	
			//this will not take seconds into account
			if(((tokens[0] == tm_set->tm_hour) && (tokens[1] == tm_set->tm_min)) || ((tokens[0] == tm_due->tm_hour) && (tokens[1] == tm_due->tm_min)))
			{
				found.push_back(get_list()[i].get_item_id());
			}
		}
	}
	/* for debugging the found vector
	for(int i = 0; i < found.size(); i++)
	{
		cout << found[i] << endl;
	}
	*/
	return found;
}

void TodoList::delete_item(int id){
	vector<Item> new_list;
	for(int i = 0; i < get_item_count(); i++)
	{
		if(!(id == get_list()[i].get_item_id())){
			cout << get_list()[i] << endl;
			new_list.push_back(get_list()[i]);
		}
	}
	swap_list(new_list);
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
	list1.add_item("test 2", "big stinky description", time(NULL), time(NULL));
	list1.add_item("search BIG","desc", time(NULL), time(NULL));
	display(list1);
	list1.search_item("search");
	list1.search_item("test");
	list1.search_item("13:23:00");
	list1.search_item("10:41:00");
	list1.delete_item(2);
	display(list1);
	cout << list1.get_item_count() << endl;
	return 0;
}

