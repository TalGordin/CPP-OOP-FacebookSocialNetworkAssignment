#ifndef _USER_H
#define _USER_H

#include "ex1.h"
#include "page.h"
#include "socialnetwork.h"
#include "status.h"

class Page;
class SocialNetwork;
class Status;
#include <vector>
#include <string>

class User
{
	std::string name;
	Date DOB; //date of birth
	std::vector<Status*> wall;
	std::vector<User*> friendsArr;
	std::vector<Page*> followedPages;

public:
	User(int day, int month, int year, std::string name); //c'tor
	User(const User& copiedUser); // copy c'tor
	User(const User&& movedUser) noexcept(true); //move c'tor
	~User();

	//get func
	const std::string& getName() const;
	const date& getDateOfBirth() const;
	const std::vector<Status*>& getWall() const;
	const std::vector<User*> getConnections() const;
	const std::vector<Page*> getFollowedPages() const;

	//set func
	void setName(std::string& name);
	void setDateOfBirth(date& newDOB);
	void setWall(Status& newStatus);
	void setConnections(User& newFriend);
	void setfollowedPages(Page& newPage);
	void setStatus(std::string& text);

	// methods
		//operators:
	const User& operator+=(User& newFriend);
	const bool operator>(User& other);

	void reallocConnections();
	void reallocWall();
	void reallocfollowedPages();
	bool friendRequest(User& reqwestedUser);
	void unfriend(std::string& name);
	void showAllUserStatuses();
	void show10LatestFriendsStatuses();
	void showAllFriends(); 
	void showAllFollowedPages();
	bool addPageToFollowedPages(Page& page, bool noErrMsg = false); //When using this function, only send page.
	bool removePageFromFollowedPages(Page& page, bool noErrMsg = false); //When using this function, only send page.
	User* findFriend(const std::string& name);
	Page* findPage(const std::string& name);
	void createNewStatus();

private:
	void unfriendOneSide(User& reqwestedUser);
};
#endif
