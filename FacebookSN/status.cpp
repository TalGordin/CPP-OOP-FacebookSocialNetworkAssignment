#include "status.h"
using namespace std;
//********************************************************************************

//c'tor
Status::Status(std::string text) {
	setTime();
	this->text = text;
}

Status::Status(const Status& oldStatus)
{
	setTime();
	this->text = oldStatus.getStatus();
}

//********************************************************************************

//get funcs: allows access to the class attributes
const Time Status::getTime() const
{
	return time;
}

const std::string Status::getStatus() const
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

const bool Status::operator==(Status& other)
{
	return (text == other.getStatus());
}

//prints the status
void Status::printStatus()
{
	std::cout << "Created on: " << std::setfill('0') << std::setw(2) << time.date.day << "/" << std::setfill('0') << std::setw(2) << time.date.month << "/"
		<< time.date.year << " at ";
	std::cout << std::setfill('0') << std::setw(2) << time.hours << ":";
	std::cout << std::setfill('0') << std::setw(2) << time.minutes << ".\n";
	std::cout << "\"" << text << "\"\n";
}