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
	std::string name;
	std::vector<User*> followers;
	std::vector<Status*> wall;
	Page(const Page& copiedPage); 
	// copy c'tor (deleted)
public:
	Page(const std::string& name); //c'tor
	~Page() = delete; // d'tor
	
	//get func:
	const std::string& getName() const;
	const std::vector<User*>& getFollowers() const;
	const std::vector<Status*>& getWall() const;

	//set func:
	void setname(std::string& newName);
	void setFollowers(User& newFollower);
	void setWall(Status& newStatus);
	void setStatus(std::string& text);

	//methods
	void reallocWall();
	void reallocFollowers();
	void showAllStatuses();
	bool addUserToPageFollowers(User& follower, bool noErrMsg = false); //When using this function, only send follower.
	bool removeUserFromPageFollowers(User& follower, bool noErrMsg = false); //When using this function, only send follower.
	void showUsersList();
	void createNewStatus();
	User* findFollower(const std::string& name);
};

#endif
