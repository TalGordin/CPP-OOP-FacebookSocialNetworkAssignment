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
	vector<User*> allUsers;
	vector<Page*> allPages;
	SocialNetwork(const SocialNetwork& facebook);

public:
	SocialNetwork(); //c'tor
	~SocialNetwork(); // dec'tor

	//get funcs:
	const vector<User*> getAllUsers();
	const vector<Page*> getAllPages();
	const int getUsersAmount();
	const int getPagesAmount();

	//set funcs:
	User* setUser(int day, int month, int year, string& name);
	Page* setPage(const string& name);

	//methods
	User* findUser(const string name);
	Page* findPage(const string name);
	void reallocUsersArr();
	void reallocPagesArr();
	void showAllAccounts();
	void initializeFaceBookUsers();
};

#endif
