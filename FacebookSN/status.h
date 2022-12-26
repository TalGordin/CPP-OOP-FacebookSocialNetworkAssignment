#ifndef __STATUS_H
#define __STATUS_H
#include "ex1.h"

class Page;
class SocialNetwork;
class User;

class Status
{
	Time time;
	std::string text = nullptr; //TO ASK KEREN - is there a need for std::string?
	Status(const Status& oldStatus); // copy c'tor

public:
	Status(std::string text); //c'tor
	// d'tor not needed, string destructs itself

	//get func:
	const Time getTime() const;
	const std::string getStatus() const;

	// set func:
	void setTime();

	//methods
	void printStatus();

};

#endif
