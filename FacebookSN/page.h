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
	string name;
	vector<User*> followers;
	vector<Status*> wall;
	Page(const Page& copiedPage); 
	// copy c'tor (deleted)
public:
	Page(const string& name); //c'tor
	~Page() = delete; // d'tor
	
	//get func:
	const string& getName() const;
	const vector<User*>& getFollowers() const;
	const vector<Status*>& getWall() const;

	//set func:
	void setname(string& newName);
	void setFollowers(User& newFollower);
	void setWall(Status& newStatus);
	void setStatus(string& text);

	//methods
	void reallocWall();
	void reallocFollowers();
	void showAllStatuses();
	bool addUserToPageFollowers(User& follower, bool noErrMsg = false); //When using this function, only send follower.
	bool removeUserFromPageFollowers(User& follower, bool noErrMsg = false); //When using this function, only send follower.
	void showUsersList();
	void createNewStatus();
	User* findFollower(const string& name);
};

#endif
