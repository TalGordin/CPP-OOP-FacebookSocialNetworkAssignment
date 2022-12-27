#include "socialnetwork.h"
using namespace std;
//********************************************************************************

//get funcs: allows access to the class attributes
const std::vector<User*> SocialNetwork::getAllUsers()
{
	return allUsers;
}

const std::vector<Page*> SocialNetwork::getAllPages()
{
	return allPages;
}

const int SocialNetwork::getUsersAmount() 
{
	return allUsers.size();
}

const int SocialNetwork::getPagesAmount() 
{
	return allPages.size();
}

//********************************************************************************

//set funcs: insert values into class attributes
User* SocialNetwork::setUser(int day, int month, int year, std::string& name)
{
	if (allUsers.size() == allUsers.capacity())
		allUsers.reserve(2 * allUsers.capacity());

	User* newUser = new User(day, month, year, name);
	allUsers.push_back(newUser);

	return newUser;
}

Page* SocialNetwork::setPage(const std::string& name)
{
	if (allPages.size() == allPages.capacity())
		allPages.reserve(2 * allPages.capacity());

	Page* newPage = new Page(name);
	allPages.push_back(newPage);

	return newPage;
}

//********************************************************************************

//methods

//Searches for user in the social network. If found, returns pointer to user, else, returns nullptr.
User* SocialNetwork::findUser(const std::string name)
{
	unsigned int size = allUsers.size();
	std::vector<User*>::iterator itr = allUsers.begin();
	std::vector<User*>::iterator end = allUsers.end();

	for (; itr != end; ++itr)
	{
		if ((*itr)->getName() == name)
			return *itr;
	}
	return nullptr; //If not found, returns null.
}
//Searches for page in the social network. If found, returns pointer to page, else, returns nullptr.
Page* SocialNetwork::findPage(const std::string name)
{
	unsigned int size = allPages.size();
	std::vector<Page*>::iterator itr = allPages.begin();
	std::vector<Page*>::iterator end = allPages.end();

	for (; itr != end; ++itr)
	{
		if ((*itr)->getName() == name)
			return *itr;
	}
	return nullptr; //If not found, returns null.
}
//prints out all pages and users in the social network
void SocialNetwork::showAllAccounts()
{
	std::cout << "Users in the system: \n";
	std::cout << "~ ~ ~ ~ ~\n";

	std::vector<User*>::iterator uItr = allUsers.begin();
	std::vector<User*>::iterator uItrEnd = allUsers.end();

	for (; uItr != uItrEnd; ++uItr)
		std::cout << (*uItr)->getName() << "\n";
	
	std::cout << "~ ~ ~ ~ ~\n\n";

	std::cout << "Pages in the system: \n";
	std::cout << "~ ~ ~ ~ ~\n";

	std::vector<Page*>::iterator pItr = allPages.begin();
	std::vector<Page*>::iterator pItrEnd = allPages.end();

	for (; pItr != pItrEnd; ++pItr)
		std::cout << (*pItr)->getName() << "\n";

	std::cout << "~ ~ ~ ~ ~\n\n";
}
//For ease of testing, inserts premade users and pages to the social network
void SocialNetwork::initializeFaceBookUsers()
{
	
// INSERT 3 USERS:
	std::string name1 = "Avital", name2 = "Archie", name3 = "Bizo";

	setUser(5, 2, 1998, name1);
	setUser(15, 4, 2021, name2);
	setUser(7, 6, 2018, name3);
// INSERT 3 PAGES:

	std::string name4 = "Hogwarts", name5 = "Academit TAY", name6 = "Microsoft";

	setPage(name4);
	setPage(name5);
	setPage(name6);
// INSERT STATUSES:

//USERS:

	std::string text1 = "I hope I get 100 :D";
	std::string text2 = "Just a tired student trying to get by.";
	std::string text3 = "I hope I get food :D";
	std::string text4 = "Let me into the room, hooman.";
	std::string text5 = "What's up, my brothers?";
	std::string text6 = "Woof Woof :3";

	std::vector<User*>::iterator uItr = allUsers.begin();
	/**/
	(*uItr)->setStatus(text1);
	(*uItr)->setStatus(text2);

	++uItr;
	(*uItr)->setStatus(text3);
	(*uItr)->setStatus(text4);

	++uItr;
	(*uItr)->setStatus(text5);
	(*uItr)->setStatus(text6);

//PAGES:

	std::string text7 = "Welcome, Harry :D";
	std::string text8 = "We hate Slytherin";
	std::string text9 = "Good luck with Calculus";
	std::string text10 = "You're gonna need it";
	std::string text11 = "Come work with us we have an ice cream machine :D";
	std::string text12 = "Please update to Windows 11!";

	std::vector<Page*>::iterator pItr = allPages.begin();

	(*pItr)->setStatus(text7);
	(*pItr)->setStatus(text8);

	++pItr;
	(*pItr)->setStatus(text9); 
	(*pItr)->setStatus(text10);

	++pItr;
	(*pItr)->setStatus(text11);
	(*pItr)->setStatus(text12);
	
// CREATING FRIENDSHIPS

	std::vector<User*>::iterator itr0, itr1, itr2;
	itr0 = allUsers.begin();
	itr1 = itr0 + 1;
	itr2 = itr1 + 1;

	(*itr0)->friendRequest(**itr1);
	(*itr1)->friendRequest(**itr2);
	(*itr2)->friendRequest(**itr0);
	
}