#include "Page.h"
using namespace std;

//************************************************************************************

//c'tor 
Page::Page(const char* name)
{
	this->name = new char[strlen(name) + 1];
	checkMemory(this->name);
	strcpy(this->name, name);

	followers.arrOfUsers = new User * [MIN_FOLLOWERS_NUM];
	checkMemory(followers.arrOfUsers);
	followers.phySize = MIN_FOLLOWERS_NUM;

	wall.arrOfStatuses = new Status * [MIN_STATUS_NUM];
	checkMemory(wall.arrOfStatuses);
	wall.phySize = MIN_STATUS_NUM;
}

//d'tor
Page:: ~Page()
{
	delete(name);
	delete(followers.arrOfUsers);
	delete(wall.arrOfStatuses);
}

//********************************************************************************

//get funcs: allows access to the class attributes
char* Page::getName() const
{
	return name;
}

UsersArr Page::getFollowers() const
{
	return followers;
}

StatusesArr Page::getWall() const
{
	return wall;
}

//***********************************************************************************

//set funcs: insert values into class attributes
void Page::setname(char* newName)
{
	strcpy(name, newName);
}

void Page::setFollowers(User& newFollower)
{
	if (followers.logSize == followers.phySize)
	{
		followers.phySize = followers.phySize * 2;
		reallocFollowers();
	}
	followers.logSize++;
	followers.arrOfUsers[followers.logSize] = &newFollower;
}

void Page::reallocFollowers()
{
	followers.phySize *= 2;
	User** tempArr = new User * [followers.phySize];
	checkMemory(tempArr);
	for (int i = 0; i < followers.logSize; i++)
		tempArr[i] = followers.arrOfUsers[i];

	delete[](followers.arrOfUsers);
	followers.arrOfUsers = tempArr;
}

void Page::setWall(Status& newStatus)
{
	if (wall.logSize == wall.phySize)
	{
		wall.phySize = wall.phySize * 2;
		reallocWall();
	}
	wall.logSize++;
	wall.arrOfStatuses[wall.logSize] = &newStatus;
}

void Page::reallocWall()
{
	Status** tempArr = new Status * [wall.phySize];
	checkMemory(tempArr);
	for (int i = 0; i < wall.logSize; i++)
		tempArr[i] = wall.arrOfStatuses[i];

	delete[](wall.arrOfStatuses);
	wall.arrOfStatuses = tempArr;
}

void Page::setStatus(char* text)
{
	if (wall.logSize == wall.phySize)
		reallocWall();

	wall.arrOfStatuses[wall.logSize] = new Status(text);
	wall.logSize++;
}

//********************************************************************

//methods:

//Shows all statuses of page
void Page::showAllStatuses() 
{
	int size = wall.logSize;
	if (size == 0)
		cout << "You have no statuses on your wall!\n";
	else
	{
		cout << "Showing all statuses for page " << name << ":\n";
		cout << "~ ~ ~ ~ ~\n\n";
		for (int i = 0; i < size; i++)
		{
			wall.arrOfStatuses[i]->printStatus();
			cout << "\n";
		}
		cout << "~ ~ ~ ~ ~\n";
	}
}
//adds user to followers of page. When using this function, only send follower.
bool Page::addUserToPageFollowers(User& follower, bool noErrMsg)
{
	User* searchedUser = findFollower(follower.getName());

	if (searchedUser == nullptr)
	{
		if (followers.logSize == followers.phySize)
			reallocFollowers();

		followers.arrOfUsers[followers.logSize] = &follower;
		followers.logSize++;
		follower.addPageToFollowedPages(*this, true);
		return true;
	}
	else
		if (!noErrMsg) //Meaning, we're not here because of a loop
		{
			cout << follower.getName() << " is already following your page!\n";
			return false;
		}
	return true;
}
//removes user from followers of page. When using this function, only send follower.
bool Page::removeUserFromPageFollowers(User& follower, bool noErrMsg)
{
	for (int i = 0; i < followers.logSize; i++)
	{
		if (strcmp(followers.arrOfUsers[i]->getName(), follower.getName()) == 0)
		{
			followers.arrOfUsers[i] = nullptr;

			for (int j = i; j < followers.logSize - 1; j++)
				followers.arrOfUsers[i] = followers.arrOfUsers[i + 1];

			followers.logSize--;
			follower.removePageFromFollowedPages(*this, true);
			return true;
		}
	}

	if (!noErrMsg)
	{
		cout << follower.getName() << " isn't following your page!\n";
		return false;
	}
	return true;
}
//creates a new status for the page
void Page::createNewStatus()
{
	char text[MAX_STATUS_LEN];
	cout << "Please type in your status (up to " << MAX_STATUS_LEN << " characters): \n";
	cin.ignore();
	cin.getline(text, MAX_STATUS_LEN);

	setStatus(text);
	cout << "\n" << this->name << ", Your new status has been posted!\n\n";
}
//searches a follower in followers list. Returns pointer to follower if found, else returns nullptr
User* Page::findFollower( const char* name)
{
	for (int i = 0; i < followers.logSize; i++)
	{
		if (strcmp(name, followers.arrOfUsers[i]->getName()) == 0)
			return followers.arrOfUsers[i];
	}
	return nullptr;
}
//prints all followers of page
void Page::showUsersList()
{
	int size = followers.logSize;
	if (size == 0)
		cout << "You have no followers!\n";
	else
	{
		cout << name << "'s followers: \n";
		cout << "~ ~ ~ ~ ~\n";
		for (int i = 0; i < size; i++)
			cout << followers.arrOfUsers[i]->getName() << "\n";
		cout << "~ ~ ~ ~ ~\n";
	}
}