#ifndef __STATUS_H
#define __STATUS_H
#include "ex1.h"

class Page;
class SocialNetwork;
class User;

class Status
{
	Time time;
	char* text = nullptr;
	Status(const Status& oldStatus); // copy c'tor

public:
	Status(char* text); //c'tor
	~Status(); // d'tor

	//get func:
	Time getTime() const;
	char* getStatus() const;

	// set func:
	void setTime();

	//methods
	void printStatus();

};

#endif
