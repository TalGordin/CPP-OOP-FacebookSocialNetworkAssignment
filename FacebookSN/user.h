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
	string name;
	Date DOB; //date of birth
	vector<Status*> wall;
	vector<User*> friendsArr;
	vector<Page*> followedPages;
	User(const User& user); // copy c'tor

public:
	User(int day, int month, int year, string name); //c'tor
	~User() = delete;

	//get func
	const string& getName() const;
	const date& getDateOfBirth() const;
	const vector<Status*>& getWall() const;
	const vector<User*>& getConnections() const;
	const vector<Page*>& getFollowedPages() const;

	//set func
	void setName(string& name);
	void setDateOfBirth(date& newDOB);
	void setWall(Status& newStatus);
	void setConnections(User& newFriend);
	void setfollowedPages(Page& newPage);
	void setStatus(string& text);

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
	User* findFriend(const string& name);
	Page* findPage(const string& name);
	void createNewStatus();

private:
	void unfriendOneSide(User& reqwestedUser);
};
#endif
