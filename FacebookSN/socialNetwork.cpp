#include "socialnetwork.h"
using namespace std;

//********************************************************************************

//c'tor
SocialNetwork::SocialNetwork() {
	allUsers.arrOfUsers = new User * [MIN_CONNECTIONS_NUM];
	checkMemory(allUsers.arrOfUsers);
	allUsers.arrOfUsers[0] = nullptr;
	allUsers.logSize = 0;
	allUsers.phySize = MIN_CONNECTIONS_NUM;

	allPages.arrOfPages = new Page * [MIN_PAGES_NUM];
	checkMemory(allPages.arrOfPages);
	allPages.arrOfPages[0] = nullptr;
	allPages.logSize = 0;
	allPages.phySize = MIN_PAGES_NUM;
} //c'tor

//d'tor
SocialNetwork::~SocialNetwork() {
	for (int i = 0; i < allUsers.logSize; i++)
		delete allUsers.arrOfUsers[i];
	delete[]allUsers.arrOfUsers;

	for (int i = 0; i < allPages.logSize; i++)
		delete allPages.arrOfPages[i];
	delete[]allPages.arrOfPages;
} // d'tor

//********************************************************************************

//get funcs: allows access to the class attributes
UsersArr SocialNetwork::getAllUsers()
{
	return allUsers;
}

PagesArr SocialNetwork::getAllPages()
{
	return allPages;
}

int SocialNetwork::getUsersAmount() {
	return allUsers.logSize;
}

int SocialNetwork::getPagesAmount() {
	return allPages.logSize;
}

//********************************************************************************

//set funcs: insert values into class attributes
User* SocialNetwork::setUser(int day, int month, int year, char* name)
{
	if (allUsers.logSize == allUsers.phySize)
		reallocUsersArr();


	allUsers.arrOfUsers[allUsers.logSize] = new User(day, month, year, name);
	allUsers.logSize++;

	return allUsers.arrOfUsers[allUsers.logSize - 1];
}

Page* SocialNetwork::setPage(const char* name)
{
	if (allPages.logSize == allPages.phySize)
		reallocPagesArr();

	allPages.arrOfPages[allPages.logSize] = new Page(name);
	allPages.logSize++;

	return allPages.arrOfPages[allPages.logSize - 1];
}

//********************************************************************************

//methods

//Searches for user in the social network. If found, returns pointer to user, else, returns nullptr.
User* SocialNetwork::findUser(const char* name)
{
	for (int i = 0; i < allUsers.logSize; i++)
	{
		if (strcmp(allUsers.arrOfUsers[i]->getName(), name) == 0)
			return allUsers.arrOfUsers[i];
	}
	return nullptr; //If not found, returns null.
}
//Searches for page in the social network. If found, returns pointer to page, else, returns nullptr.
Page* SocialNetwork::findPage(const char* name)
{
	for (int i = 0; i < allPages.logSize; i++)
	{
		if (strcmp(allPages.arrOfPages[i]->getName(), name) == 0)
			return allPages.arrOfPages[i];
	}
	return nullptr; //If not found, returns null.
}
//reallocs array of users
void SocialNetwork::reallocUsersArr()
{
	allUsers.phySize *= 2;
	User** tempArr = new User * [allUsers.phySize];
	checkMemory(tempArr);
	for (int i = 0; i < allUsers.logSize; i++)
		tempArr[i] = allUsers.arrOfUsers[i];

	delete[](allUsers.arrOfUsers);
	allUsers.arrOfUsers = tempArr;
}
//reallocs array of page
void SocialNetwork::reallocPagesArr()
{
	allPages.phySize *= 2;
	Page** tempArr = new Page * [allPages.phySize];
	checkMemory(tempArr);
	for (int i = 0; i < allPages.logSize; i++)
		tempArr[i] = allPages.arrOfPages[i];

	delete[](allPages.arrOfPages);
	allPages.arrOfPages = tempArr;
}
//prints out all pages and users in the social network
void SocialNetwork::showAllAccounts()
{
	cout << "Users in the system: \n";
	cout << "~ ~ ~ ~ ~\n";

	for (int i = 0; i < allUsers.logSize; i++)
		cout << (allUsers.arrOfUsers[i]->getName()) << "\n";
	
	cout << "~ ~ ~ ~ ~\n\n";

	cout << "Pages in the system: \n";
	cout << "~ ~ ~ ~ ~\n";

	for (int i = 0; i < allPages.logSize; i++)
		cout << (allPages.arrOfPages[i]->getName()) << "\n";

	cout << "~ ~ ~ ~ ~\n\n";
}
//For ease of testing, inserts premade users and pages to the social network
void SocialNetwork::initializeFaceBookUsers()
{
// INSERT 3 USERS:
	char name1[MAX_NAME_LEN];
	char name2[MAX_NAME_LEN];
	char name3[MAX_NAME_LEN];

	strcpy(name1, "Avital");
	strcpy(name2, "Archie");
	strcpy(name3, "Bizo");

	setUser(5, 2, 1998, name1);
	setUser(15, 4, 2021, name2);
	setUser(7, 6, 2018, name3);

// INSERT 3 PAGES:

	char name4[MAX_NAME_LEN];
	char name5[MAX_NAME_LEN];
	char name6[MAX_NAME_LEN];

	strcpy(name4, "Hogwarts");
	strcpy(name5, "Academit TA-Y");
	strcpy(name6, "Microsoft");

	setPage(name4);
	setPage(name5);
	setPage(name6);
	
// INSERT STATUSES:

//USERS:

	char text1[MAX_STATUS_LEN] = "I hope I get 100 :D";
	char text2[MAX_STATUS_LEN] = "Just a tired student trying to get by.";
	char text3[MAX_STATUS_LEN] = "I hope I get food :D";
	char text4[MAX_STATUS_LEN] = "Let me into the room, hooman.";
	char text5[MAX_STATUS_LEN] = "What's up, my brothers?";
	char text6[MAX_STATUS_LEN] = "Woof Woof :3";

	allUsers.arrOfUsers[0]->setStatus(text1);
	allUsers.arrOfUsers[0]->setStatus(text2);
	allUsers.arrOfUsers[1]->setStatus(text3);
	allUsers.arrOfUsers[1]->setStatus(text4);
	allUsers.arrOfUsers[2]->setStatus(text5);
	allUsers.arrOfUsers[2]->setStatus(text6);

//PAGES:

	char text7[MAX_STATUS_LEN] = "Welcome, Harry :D";
	char text8[MAX_STATUS_LEN] = "We hate Slytherin";
	char text9[MAX_STATUS_LEN] = "Good luck with Calculus";
	char text10[MAX_STATUS_LEN] = "You're gonna need it";
	char text11[MAX_STATUS_LEN] = "Come work with us we have an ice cream machine :D";
	char text12[MAX_STATUS_LEN] = "Please update to Windows 11!";

	allPages.arrOfPages[0]->setStatus(text7);
	allPages.arrOfPages[0]->setStatus(text8);
	allPages.arrOfPages[1]->setStatus(text9);
	allPages.arrOfPages[1]->setStatus(text10);
	allPages.arrOfPages[2]->setStatus(text11);
	allPages.arrOfPages[2]->setStatus(text12);

// CREATING FRIENDSHIPS

	allUsers.arrOfUsers[0]->friendRequest(*(allUsers.arrOfUsers[1]));
	allUsers.arrOfUsers[1]->friendRequest(*(allUsers.arrOfUsers[2]));
	allUsers.arrOfUsers[2]->friendRequest(*(allUsers.arrOfUsers[0]));
}