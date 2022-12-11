#ifndef _PAGE_H
#define _PAGE_H

#include "ex1.h"
#include "user.h"
#include "status.h"
#include "socialnetwork.h"

class Status;
class User;
class SocialNetwork;

class Page
{
	char* name;
	UsersArr followers;
	StatusesArr wall;
	Page(const Page& copiedPage); 
	// copy c'tor (deleted)
public:
	Page(const char* name); //c'tor
	~Page(); // d'tor
	
	//get func:
	char* getName() const;
	UsersArr getFollowers() const;
	StatusesArr getWall() const;

	//set func:
	void setname(char* newName);
	void setFollowers(User& newFollower);
	void setWall(Status& newStatus);
	void setStatus(char* text);

	//methods
	void reallocWall();
	void reallocFollowers();
	void showAllStatuses();
	bool addUserToPageFollowers(User& follower, bool noErrMsg = false); //When using this function, only send follower.
	bool removeUserFromPageFollowers(User& follower, bool noErrMsg = false); //When using this function, only send follower.
	void showUsersList();
	void createNewStatus();
	User* findFollower(const char* name);
};

#endif
