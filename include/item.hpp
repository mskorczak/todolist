#include <string>

using namespace std;

class Item
{
	public:
		Item(int id, string title, string desc, time_t time_set, time_t time_due);
		void set_item_status(bool status);
		string get_item_title() const;
		string get_item_desc() const;
		int get_item_id() const;
		time_t get_item_time_set() const;
		time_t get_item_time_due() const;
		bool get_item_status() const;
		friend ostream& operator<<(ostream& os, const Item& item);
	private:
		int item_id;
		string item_title;
		string item_desc;
		time_t item_time_set;
		time_t item_time_due;
		bool item_status;
};
