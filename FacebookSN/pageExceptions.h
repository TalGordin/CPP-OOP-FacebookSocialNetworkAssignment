#ifndef _PageExceptions_
#define _PageExceptions_
#include "ex1.h"
using namespace std;
#include <stdexcept>

class PageException : public std::exception
{
public:
	const char* followerNotFound() { return "User not found in followers list!"; }
	const char* noStatusesToPrint() { return "You have no statuses on your wall!"; }
	const char* userAlreadyFollows() { return "This user is already following your page!"; }
	const char* noFollowers() { return "Your page has no followers!"; }
	const char* emptyWall() { return "this page has no statuses on their wall!"; }
};


#endif // _PageExceptions_