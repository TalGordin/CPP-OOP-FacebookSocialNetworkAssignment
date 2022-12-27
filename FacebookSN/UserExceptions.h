#ifndef _UserExceptions_
#define _UserExceptions_
#include "ex1.h"
using namespace std;
#include <stdexcept>

class UserException : public std::exception
{
public:
	const char* friendNotFound() { return "User not found in friends list!";}
	const char* noFollowedPages() { return "You're not following any pages!"; }
	const char* pageNotFound() { return "Page not found in followed pages list!"; }
	const char* alreadyFriends() { return "You're already friends with that user!"; }
	const char* alreadyFollowing() { return "You're already following that page!"; }
	const char* sendFriendReqwestToYourself() { return "You're already friends with that user!"; }
	const char* emptyWall() { return "this user has no statuses on their wall!"; }
	const char* noFriends() { return "this user has no friends at the moment!"; }
};


#endif // _UserExceptions_
