#ifndef _USER_H
#define _USER_H

#include "ex1.h"
#include "page.h"
#include "socialnetwork.h"
#include "status.h"

class Page;
class SocialNetwork;
class Status;

class User
{
	char* name;
	Date DOB; //date of birth
	StatusesArr wall;
	UsersArr friendsArr;
	PagesArr followedPages;
	User(const User& user); // copy c'tor

public:
	User(int day, int month, int year, char* name); //c'tor
	~User(); // d'tor

	//get func
	char* getName() const;
	date getDateOfBirth() const;
	StatusesArr getWall() const;
	UsersArr getConnections() const;
	PagesArr getFollowedPages() const;

	//set func
	void setName(char* name);
	void setDateOfBirth(date newDOB);
	void setWall(Status& newStatus);
	void setConnections(User& newFriend);
	void setfollowedPages(Page& newPage);
	void setStatus(char* text);

	// methods
	void reallocConnections();
	void reallocWall();
	void reallocfollowedPages();
	bool friendRequest(User& reqwestedUser);
	void unfriend(User& reqwestedUser);
	void showAllUserStatuses();
	void show10LatestFriendsStatuses();
	void showAllFriends(); 
	void showAllFollowedPages();
	bool addPageToFollowedPages(Page& page, bool noErrMsg = false); //When using this function, only send page.
	bool removePageFromFollowedPages(Page& page, bool noErrMsg = false); //When using this function, only send page.
	User* findFriend(const char* name);
	Page* findPage(const char* name);
	void createNewStatus();

private:
	void unfriendOneSide(User& reqwestedUser);
};
#endif
