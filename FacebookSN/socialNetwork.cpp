#include "socialnetwork.h"
using namespace std;

//********************************************************************************

//c'tor
SocialNetwork::SocialNetwork() 
{
	allUsers.push_back(nullptr);
	allPages.push_back(nullptr);
} //c'tor

//d'tor
SocialNetwork::~SocialNetwork() 
{
	vector<User*>::iterator usersItr = allUsers.begin();
	vector<User*>::iterator usersEnd = allUsers.end();

	for (; usersItr != usersEnd; ++usersItr)
		delete *usersItr;

	vector<Page*>::iterator pagesItr = allPages.begin();
	vector<Page*>::iterator pagesEnd = allPages.end();

	for (; pagesItr != pagesEnd; ++pagesItr)
		delete *pagesItr;
} // d'tor

//********************************************************************************

//get funcs: allows access to the class attributes
const vector<User*> SocialNetwork::getAllUsers()
{
	return allUsers;
}

const vector<Page*> SocialNetwork::getAllPages()
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
User* SocialNetwork::setUser(int day, int month, int year, string& name)
{
	if (allUsers.size() == allUsers.capacity())
		allUsers.reserve(2 * allUsers.capacity());

	User* newUser = new User(day, month, year, name);
	allUsers.push_back(newUser);

	return newUser;
}

Page* SocialNetwork::setPage(const string& name)
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
User* SocialNetwork::findUser(const string name)
{
	unsigned int size = allUsers.size();
	vector<User*>::iterator itr = allUsers.begin();
	vector<User*>::iterator end = allUsers.end();

	for (; itr != end; ++itr)
	{
		if ((*itr)->getName() == name)
			return *itr;
	}
	return nullptr; //If not found, returns null.
}
//Searches for page in the social network. If found, returns pointer to page, else, returns nullptr.
Page* SocialNetwork::findPage(const string name)
{
	unsigned int size = allPages.size();
	vector<Page*>::iterator itr = allPages.begin();
	vector<Page*>::iterator end = allPages.end();

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
	cout << "Users in the system: \n";
	cout << "~ ~ ~ ~ ~\n";

	vector<User*>::iterator uItr = allUsers.begin();
	vector<User*>::iterator uItrEnd = allUsers.end();

	for (; uItr != uItrEnd; ++uItr)
		cout << (*uItr)->getName() << "\n";
	
	cout << "~ ~ ~ ~ ~\n\n";

	cout << "Pages in the system: \n";
	cout << "~ ~ ~ ~ ~\n";

	vector<Page*>::iterator pItr = allPages.begin();
	vector<Page*>::iterator pItrEnd = allPages.end();

	for (; pItr != pItrEnd; ++pItr)
		cout << (*pItr)->getName() << "\n";

	cout << "~ ~ ~ ~ ~\n\n";
}
//For ease of testing, inserts premade users and pages to the social network
void SocialNetwork::initializeFaceBookUsers()
{
// INSERT 3 USERS:
	string name1 = "Avital", name2 = "Archie", name3 = "Bizo";

	setUser(5, 2, 1998, name1);
	setUser(15, 4, 2021, name2);
	setUser(7, 6, 2018, name3);

// INSERT 3 PAGES:

	string name4 = "Hogwarts", name5 = "Academit TA-Y", name6 = "Microsoft";

	setPage(name4);
	setPage(name5);
	setPage(name6);
	
// INSERT STATUSES:

//USERS:

	string text1 = "I hope I get 100 :D";
	string text2 = "Just a tired student trying to get by.";
	string text3 = "I hope I get food :D";
	string text4 = "Let me into the room, hooman.";
	string text5 = "What's up, my brothers?";
	string text6 = "Woof Woof :3";

	vector<User*>::iterator uItr = allUsers.begin();

	(*uItr)->setStatus(text1);
	(*uItr)->setStatus(text2);

	++uItr;
	(*uItr)->setStatus(text3);
	(*uItr)->setStatus(text4);

	++uItr;
	(*uItr)->setStatus(text3);
	(*uItr)->setStatus(text4);

//PAGES:

	string text7 = "Welcome, Harry :D";
	string text8 = "We hate Slytherin";
	string text9 = "Good luck with Calculus";
	string text10 = "You're gonna need it";
	string text11 = "Come work with us we have an ice cream machine :D";
	string text12 = "Please update to Windows 11!";

	vector<Page*>::iterator pItr = allPages.begin();

	(*uItr)->setStatus(text7);
	(*uItr)->setStatus(text8);

	++uItr;
	(*uItr)->setStatus(text9);
	(*uItr)->setStatus(text10);

	++uItr;
	(*uItr)->setStatus(text11);
	(*uItr)->setStatus(text12);

// CREATING FRIENDSHIPS

	uItr = allUsers.begin();

	vector<User*>::iterator itr0, itr1, itr2;
	itr0 = allUsers.begin();
	itr1 = itr0 + 1;
	itr2 = itr1 + 1;

	(*itr0)->friendRequest(**itr1);
	(*itr1)->friendRequest(**itr2);
	(*itr2)->friendRequest(**itr0);
}