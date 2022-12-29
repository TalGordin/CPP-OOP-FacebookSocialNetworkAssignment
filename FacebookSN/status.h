#ifndef __STATUS_H
#define __STATUS_H
#include "ex1.h"

class Page;
class SocialNetwork;
class User;
#include <string>

class Status
{
	Time time;
	string text;

public:
	Status(std::string text); //c'tor
	Status(const Status& oldStatus); // copy c'tor
	// d'tor not needed, string destructs itself

	//get func:
	const Time getTime() const;
	const std::string getStatus() const;

	// set func:
	void setTime();

	//methods
		//Operators:
	const bool operator==(Status& other);

	void printStatus();

};

#endif
