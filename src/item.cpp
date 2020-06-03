#include <iostream>
#include <string>
#include "item.hpp"

using namespace std;

Item::Item(int id, string title, string desc, time_t time_set, time_t time_due)
{
	item_id = id;
	item_title = title;
	item_desc = desc;
	item_time_set = time_set;
	item_time_due = time_due;
	item_status = false;
}

string Item::get_item_title() const
{
	return item_title;
}

int Item::get_item_id() const
{
	return item_id;
}

string Item::get_item_desc() const
{
	return item_desc;
}

time_t Item::get_item_time_set() const
{
	return item_time_set;
}

time_t Item::get_item_time_due() const
{
	return item_time_due;
}

bool Item::get_item_status() const
{
	return item_status;
}

void Item::set_item_status(bool status)
{
	cout << "function called " << item_status <<  endl;
	item_status = status;
	cout << "function done " << item_status <<  endl;
}

ostream& operator<<(ostream& os, const Item& item)
{
	os << "Item ID: " << item.get_item_id() << endl;
	os << "Item Title: " << item.get_item_title() << endl;
	os << "Item Desc: " << item.get_item_desc() << endl;
	time_t ts_t = item.get_item_time_set();
	time_t td_t = item.get_item_time_due();
	tm *ts = localtime(&ts_t);
	tm *td = localtime(&td_t);
	os << "Item Time Set: " << ts->tm_hour << ":" << ts->tm_min << endl;
	os << "Item Time Due: " << td->tm_hour << ":" << td->tm_min << endl;
	os << "Item Completion Status: " << item.get_item_status() << endl; 
	return os;
}
