#ifndef __FACEBOOK_H
#define __FACEBOOK_H

#include "ex1.h"
#include "Page.h"
#include "user.h"
#include <vector>

class User;
class Page;
class Status;

class SocialNetwork
{
	std::vector<User*> allUsers;
	std::vector<Page*> allPages;

public:
	SocialNetwork() = default; //c'tor
	SocialNetwork(const SocialNetwork& facebook) = delete;
	~SocialNetwork();
	
	//get funcs:
	const std::vector<User*> getAllUsers();
	const std::vector<Page*> getAllPages();
	const int getUsersAmount();
	const int getPagesAmount();

	//set funcs:
	User* setUser(int day, int month, int year, std::string& name);
	Page* setPage(const std::string& name);

	//methods
	User* findUser(const std::string name);
	Page* findPage(const std::string name);
	void reallocUsersArr();
	void reallocPagesArr();
	void showAllAccounts();
	void initializeFaceBookUsers();
};

#endif
