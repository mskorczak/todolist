#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <ctime>
#include <algorithm>
#include "item.hpp"
#include "todo.hpp"

using namespace std;

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

void TodoList::add_item(Item item)
{
	total_item_count++;
	todo_list.push_back(item);
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
			tm *tm_due = localtime(&due);	
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

void TodoList::delete_item(string search_term)
{
	vector<int> ids = search_item(search_term);
	for(unsigned int i = 0; i < ids.size(); i++)
	{
		delete_item(ids[i]);
	}
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

Item TodoList::get_item(int id) const
{
	for(int i = 0; i < get_item_count(); i++)
	{
		if(id == get_list()[i].get_item_id())
		{
			return get_list()[i];
		}
	}
	return Item(999,"ERROR","ERROR",time(NULL),time(NULL));
}
void TodoList::add_item_dependency(int item_id, int dependency_id)
{
	Item item = get_item(item_id);
	vector<int> dependencies = item.get_item_dependencies();
	if(find(dependencies.begin(),dependencies.end(),dependency_id) == dependencies.end())
	{
		item.add_item_dependency(dependency_id);
	}
	cout << "item adding dep" << endl << item << endl;
	delete_item(item_id);
	add_item(item);
}
