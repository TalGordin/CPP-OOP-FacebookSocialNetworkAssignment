#include "user.h"
using namespace std;

//***************************************************************

//c'tor
User::User(int day, int month, int year, char* name = nullptr) 
{
	this->name = insertUserName(name);

	DOB = insertDateOfBirth(day, month, year);

	friendsArr.arrOfUsers = new User * [MIN_CONNECTIONS_NUM];
	checkMemory(friendsArr.arrOfUsers);
	friendsArr.phySize = MIN_CONNECTIONS_NUM;
	friendsArr.logSize = 0;

	followedPages.arrOfPages = new Page * [MIN_CONNECTIONS_NUM];
	checkMemory(followedPages.arrOfPages);
	followedPages.phySize = MIN_CONNECTIONS_NUM;
	followedPages.logSize = 0;

	wall.arrOfStatuses = new Status * [MIN_STATUSES_NUM];
	checkMemory(wall.arrOfStatuses);
	wall.phySize = MIN_CONNECTIONS_NUM;
	wall.logSize = 0;
}

//d'tor
User:: ~User()
{
	delete(name);
	delete(wall.arrOfStatuses);
	delete(friendsArr.arrOfUsers);
	delete(followedPages.arrOfPages);

}

//insert func
char* insertUserName(char* tempName)
{
	char* name;
	name = new char[strlen(tempName) + 1];
	checkMemory(name);

	strcpy(name, tempName);

	return name;
}

date insertDateOfBirth(int day, int month, int year)
{
	date date;
	
	date.year = year;
	date.month = month;
	date.day = day;

	return date;
}

//***************************************************************************************************

//get func

char* User::getName() const
{
	return name;
}

date User::getDateOfBirth() const
{
	return DOB;
}

StatusesArr User::getWall() const
{
	return wall;
}

//gets list of all friends the user has (the connections with other users)
UsersArr User::getConnections() const
{
	return friendsArr;
}

PagesArr User::getFollowedPages() const
{
	return followedPages;
}

//*******************************************************************************************************

//set func 
void User::setName(char* newName) // remember to free new name 
{
	strcpy(name, newName);
}

void User::setDateOfBirth(date newDOB)
{
	DOB = newDOB;
}

void User::setWall(Status& newStatus)
{
	if (wall.logSize == wall.phySize)
		reallocWall();

	wall.logSize++;
	wall.arrOfStatuses[wall.logSize] = &newStatus;
}

void User::reallocWall()
{
	wall.phySize *= 2;
	Status** tempArr = new Status * [wall.phySize];
	checkMemory(tempArr);
	for (int i = 0; i < wall.logSize; i++)
		tempArr[i] = wall.arrOfStatuses[i];

	delete[](wall.arrOfStatuses);
	wall.arrOfStatuses = tempArr;
}

//adds new connection (friend) to user
void User::setConnections(User& newFriend)
{
	if (friendsArr.logSize == friendsArr.phySize)
	{
		friendsArr.phySize = friendsArr.phySize * 2;
		reallocConnections();

	}
	friendsArr.arrOfUsers[friendsArr.logSize] = &newFriend;
	friendsArr.logSize++;
}
//reallocs array of user's friends
void User::reallocConnections()
{
	User** tempArr = new User * [friendsArr.phySize];
	checkMemory(tempArr);
	for (int i = 0; i < friendsArr.logSize; i++)
		tempArr[i] = friendsArr.arrOfUsers[i];

	delete[](friendsArr.arrOfUsers);
	friendsArr.arrOfUsers = tempArr;
}

void User::setfollowedPages(Page& newPage)
{
	if (followedPages.logSize == followedPages.phySize)
	{
		followedPages.phySize = followedPages.phySize * 2;
		reallocfollowedPages();

	}
	followedPages.logSize++;
	followedPages.arrOfPages[followedPages.logSize] = &newPage;
}

void User::reallocfollowedPages()
{
	Page** tempArr = new Page * [followedPages.phySize];
	checkMemory(tempArr);
	for (int i = 0; i < followedPages.logSize; i++)
		tempArr[i] = followedPages.arrOfPages[i];

	delete[](followedPages.arrOfPages);
	followedPages.arrOfPages = tempArr;
}

void User::setStatus(char* text) 
{
	if (wall.logSize == wall.phySize)
		reallocWall();

	wall.arrOfStatuses[wall.logSize] = new Status(text);
	wall.logSize++;
}

//********************************************************************************************************

//methods

//makes two users friends (each user adds the other user to friends array)
bool User::friendRequest(User& requestedUser)
{
	User* friendPtr;
	char friendName[MAX_NAME_LEN];

	strcpy(friendName, requestedUser.getName());
	friendPtr = findFriend(friendName);

	if (friendPtr != nullptr)
	{
		cout << "You're already friends with " << friendName << "!\n";
		return  false;
	}
	if (friendPtr == this)
	{
		cout << "You can't send a friendship request to yourself!\n";
		return false;
	}

	setConnections(requestedUser);
	requestedUser.setConnections(*this);
	return true;
}
//removes friendship from two users (each user removes the other user from friends array)
void User::unfriend(User& reqwestedUser)
{
	unfriendOneSide(reqwestedUser);
	reqwestedUser.unfriendOneSide(*this);
}
//prints all statuses of user
void User::showAllUserStatuses()
{
	int size = wall.logSize;
	if (size == 0)
		cout << "You have no statuses on your wall!\n";
	else 
	{
		cout << "Showing all statuses for user " << name << ":\n";
		cout << "~ ~ ~ ~ ~\n\n";
		for (int i = 0; i < size; i++)
		{
			wall.arrOfStatuses[i]->printStatus();
			cout << "\n";
		}
		cout << "~ ~ ~ ~ ~\n";
	}
}
//show the 10 most recent statuses of each friend the user has
void User::show10LatestFriendsStatuses()
{
	int amountFriends = friendsArr.logSize;
	for (int i = 0; i < amountFriends; i++)
	{
		int sizeOfWall = friendsArr.arrOfUsers[i]->getWall().logSize;
		if (sizeOfWall == 0)
			cout << friendsArr.arrOfUsers[i]->getName() << " has no statuses.\n\n";
		else
		{
			cout << friendsArr.arrOfUsers[i]->getName() << "'s latest statuses:\n\n";
			int amountStatuses = friendsArr.arrOfUsers[i]->getWall().logSize;

			for (int j = sizeOfWall - 1 ; j >= sizeOfWall - LATEST_STAT_NUM && amountStatuses > 0; j--, amountStatuses--)
			{
				friendsArr.arrOfUsers[i]->getWall().arrOfStatuses[j]->printStatus();
				cout << "\n";
			}
		}
	}

}
//prints all of user's friends
void User::showAllFriends()
{
	int size = friendsArr.logSize;
	if (size == 0)
		cout << "You have no friends at the moment.\n";
	else 
	{
		cout << name << "'s friends: \n";
		cout << "~ ~ ~ ~ ~\n";
		for (int i = 0; i < size; i++)
			cout << friendsArr.arrOfUsers[i]->getName() << "\n";
		cout << "~ ~ ~ ~ ~\n";
	}
}
//prints all pages user follows
void User::showAllFollowedPages()
{
	int size = followedPages.logSize;
	if (size == 0)
		cout << "You're not following any pages at the moment.\n";
	else
	{
		cout << name << "'s followed pages: \n";
		cout << "~ ~ ~ ~ ~\n";
		for (int i = 0; i < size; i++)
			cout << followedPages.arrOfPages[i]->getName() << "\n";
		cout << "~ ~ ~ ~ ~\n";
	}
}
//adds a new page to follow. returns true if succeeds, else returns false.
bool User::addPageToFollowedPages(Page& page, bool noErrMsg)
{
	Page* searchedPage = findPage(page.getName());

	if (searchedPage == nullptr)
	{
		if (followedPages.logSize == followedPages.phySize)
			reallocfollowedPages();

		followedPages.arrOfPages[followedPages.logSize] = &page;
		followedPages.logSize++;
		page.addUserToPageFollowers(*this, true);
		return true;
	}
	else
		if (!noErrMsg) //Meaning, we're not here because of a loop
		{
			cout << "You're already following " << page.getName() << "!\n";
			return false;
		}
	return true;
}
//removes a page from followed pages. returns true if succeeds, else returns false.
bool User::removePageFromFollowedPages(Page& page, bool noErrMsg)
{
	for (int i = 0; i < followedPages.logSize; i++)
	{
		if (strcmp(followedPages.arrOfPages[i]->getName(), page.getName()) == 0)
		{
			followedPages.arrOfPages[i] = nullptr;

			for (int j = i; j < followedPages.logSize - 1; j++)
				followedPages.arrOfPages[i] = followedPages.arrOfPages[i + 1];

			followedPages.logSize--;
			page.removeUserFromPageFollowers(*this, true);
			return true;
		}
	}
	if (!noErrMsg) //Meaning, we're not here because of a loop
	{
		cout << "You're not following " << page.getName();
		return false;
	}
	return true;
}
//searches array of friends to find a user's name. Returns pointer to user if found, else returns nullptr.
User* User::findFriend(const char* name) {
	for (int i = 0; i < friendsArr.logSize; i++)
	{
		if (strcmp(name, friendsArr.arrOfUsers[i]->getName()) == 0)
			return friendsArr.arrOfUsers[i];
	}
	return nullptr;
}
//searches array of followed pages to find a page's name. Returns pointer to page if found, else returns nullptr.
Page* User::findPage(const char* name) {
	for (int i = 0; i < followedPages.logSize; i++)
	{
		if (strcmp(name, followedPages.arrOfPages[i]->getName()) == 0)
			return followedPages.arrOfPages[i];
	}
	return nullptr;
}
//creates a new status for user.
void User::createNewStatus()
{
	char text[MAX_STATUS_LEN];
	cout << "Please type in your status (up to " << MAX_STATUS_LEN << " characters): \n";
	cin.ignore();
	cin.getline(text, MAX_STATUS_LEN);

	setStatus(text);
}
//private func that removes a user from another user's friends list.
void User::unfriendOneSide(User& reqwestedUser)
{
	int amountUsers = friendsArr.logSize;
	bool isFound = false;
	for (int i = 0; i < amountUsers && !isFound; i++)
	{
		if (strcmp(friendsArr.arrOfUsers[i]->getName(), reqwestedUser.getName()) == 0)
		{
			for (int j = i; j < amountUsers - 1; j++)
			{
				friendsArr.arrOfUsers[i] = friendsArr.arrOfUsers[i + 1];
			}
			isFound = true;
		}
	}

	friendsArr.logSize--;
}