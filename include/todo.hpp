#include <string>
#include <vector>
#include <ctime>

using namespace std;

class TodoList
{
	public:
		TodoList(string title);
		void add_item(string title, string desc, time_t set, time_t due);
		void delete_item(string search_term);
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

