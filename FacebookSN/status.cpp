#include "status.h"
#include "ex1.h"
using namespace std;

//********************************************************************************

//c'tor
Status::Status(string text) {
	setTime();
	this->text = text;
}

//********************************************************************************

//get funcs: allows access to the class attributes
const Time Status::getTime() const
{
	return time;
}

const string Status::getStatus() const
{
	return text;
}

//********************************************************************************

//set funcs: insert values into class attributes
void Status::setTime() 
{
	time_t now = std::time(0);
	tm* locTime = gmtime(&now);

	time.date.day = locTime->tm_mday;
	time.date.month = locTime->tm_mon + 1;
	time.date.year = locTime->tm_year + 1900;
	time.hours = locTime->tm_hour;
	time.minutes = locTime->tm_min;
}

//********************************************************************************

//methods: 

//prints the status
void Status::printStatus()
{
	cout << "Created on: " << std::setfill('0') << std::setw(2) << time.date.day << "/" << std::setfill('0') << std::setw(2) << time.date.month << "/"
		<< time.date.year << " at ";
	cout << std::setfill('0') << std::setw(2) << time.hours << ":";
	cout << std::setfill('0') << std::setw(2) << time.minutes << ".\n";
	cout << "\"" << text << "\"\n";
}