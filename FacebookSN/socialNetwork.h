#ifndef __FACEBOOK_H
#define __FACEBOOK_H

#include "ex1.h"
#include "Page.h"
#include "user.h"

class User;
class Page;
class Status;

class SocialNetwork
{
	UsersArr allUsers;
	PagesArr allPages;
	SocialNetwork(const SocialNetwork& facebook);

public:
	SocialNetwork(); //c'tor
	~SocialNetwork(); // dec'tor

	//get funcs:
	UsersArr getAllUsers();
	PagesArr getAllPages();
	int getUsersAmount();
	int getPagesAmount();

	//set funcs:
	User* setUser(int day, int month, int year, char* name);
	Page* setPage(const char* name);

	//methods
	User* findUser(const char* name);
	Page* findPage(const char* name);
	void reallocUsersArr();
	void reallocPagesArr();
	void showAllAccounts();
	void initializeFaceBookUsers();
};

#endif
