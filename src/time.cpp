#include <iostream>
#include <ctime>

using namespace std;

bool time_compare(string);

int main()
{
	time_t t = time(NULL);
	tm *tm = localtime(&t);
	cout << "Now : " << tm->tm_hour << ":" << tm->tm_min << endl;
	cout << "Now : " << tm->tm_hour << ":" << tm->tm_min + 10 << endl;
	cout << "Same: " << (tm->tm_hour == tm->tm_hour + 1) << endl;
	cout << "Same: " << (tm->tm_hour == stoi("09")) << endl;
	time_compare("09:51:20");
	return 0;
}

bool time_compare(string time)
{
	//this assumes that the string for time is in HH:MM:SS
	//this will be given by the gui portion
	size_t prev = 0, pos = 0;
	do{
		pos = time.find(":",prev);
		if(pos == string::npos) pos = time.length();
		string token = time.substr(prev,pos-prev);
		if(!token.empty())cout << token;
		prev = pos + 1;
	}
	while (pos < time.length() && prev < time.length());
	cout << endl;
	return true;	
}

