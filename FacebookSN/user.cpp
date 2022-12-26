#include "user.h"

//***************************************************************

//c'tor
User::User(int day, int month, int year, std::string name = nullptr)
{
	this->name = name;

	DOB = insertDateOfBirth(day, month, year);
}

//insert func

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

const std::string& User::getName() const
{
	return name;
}

const date& User::getDateOfBirth() const
{
	return DOB;
}

const std::vector<Status*>& User::getWall() const
{
	return wall;
}

//gets list of all friends the user has (the connections with other users)
const std::vector<User*> User::getConnections() const
{
	return friendsArr;
}

const std::vector<Page*> User::getFollowedPages() const
{
	return followedPages;
}

//*******************************************************************************************************

//set func 
void User::setName(std::string& newName)
{
	name = newName;
}

void User::setDateOfBirth(date& newDOB)
{
	DOB = newDOB;
}

void User::setWall(Status& newStatus)
{
	if (wall.size() == wall.capacity())
		wall.reserve(wall.capacity() * 2);

	wall.push_back(&newStatus);
}

//adds new connection (friend) to user
void User::setConnections(User& newFriend)
{
	if (friendsArr.size() == friendsArr.capacity())
		friendsArr.reserve(friendsArr.capacity() * 2);

	friendsArr.push_back(&newFriend);
}

void User::setfollowedPages(Page& newPage)
{
	if (followedPages.size() == followedPages.capacity())
		followedPages.reserve(followedPages.capacity() * 2);

	followedPages.push_back(&newPage);
}

void User::setStatus(std::string& text)
{
	Status* newStatus = new Status(text);
	checkMemory(newStatus);

	setWall(*newStatus);
}

//********************************************************************************************************

//methods

//makes two users friends (each user adds the other user to friends array)
bool User::friendRequest(User& requestedUser)
{
	User* friendPtr;
	std::string friendName;

	friendName = requestedUser.getName();
	friendPtr = findFriend(friendName);

	if (friendPtr != nullptr) //Exceptions
	{
		std::cout << "You're already friends with " << friendName << "!\n";
		return  false;
	}
	if (friendPtr == this)
	{
		std::cout << "You can't send a friendship request to yourself!\n";
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
	int size = wall.size();
	if (size == 0) //Exceptions
		std::cout << "You have no statuses on your wall!\n";
	else 
	{
		std::cout << "Showing all statuses for user " << name << ":\n"; //To ask Keren
		std::cout << "~ ~ ~ ~ ~\n\n";

		std::vector<Status*>::iterator itr = wall.begin();
		std::vector<Status*>::iterator end = wall.end();

		for (; itr != end; ++itr)
		{
			(*itr)->printStatus();
			std::cout << "\n";
		}
		std::cout << "~ ~ ~ ~ ~\n";
	}
}
//show the 10 most recent statuses of each friend the user has
void User::show10LatestFriendsStatuses()
{
	int amountFriends = friendsArr.size();

	std::vector<User*>::iterator usersItr = friendsArr.begin();
	std::vector<User*>::iterator usersItrEnd = friendsArr.end();

	for (; usersItr != usersItrEnd; ++usersItr)
	{
		int sizeOfWall = (*usersItr)->getWall().size();
		if (sizeOfWall == 0) //Exceptions
			std::cout << (*usersItr)->getName() << " has no statuses.\n\n";
		else
		{
			std::cout << (*usersItr)->getName() << "'s latest statuses:\n\n"; //To Ask Keren
			int amountStatuses = (*usersItr)->getWall().size();

			std::vector<Status*> statusesOfFriend = (*usersItr)->getWall();
			std::vector<Status*>::iterator statusItr = statusesOfFriend.end();

			for (int j = sizeOfWall - 1 ; j >=  sizeOfWall - LATEST_STAT_NUM && amountStatuses > 0; j--, amountStatuses--)
			{
				(*statusItr)->printStatus();
				std::cout << "\n";
				++statusItr;
			}
		}
	}

}
//prints all of user's friends
void User::showAllFriends()
{
	int size = friendsArr.size();
	if (size == 0) //Exceptions
		std::cout << "You have no friends at the moment.\n";
	else 
	{
		std::cout << name << "'s friends: \n";
		std::cout << "~ ~ ~ ~ ~\n";

		std::vector<User*>::iterator itr = friendsArr.begin();
		std::vector<User*>::iterator end = friendsArr.end();

		for (; itr != end; ++itr)
		{
			(*itr)->getName();
			std::cout << "\n";
		}
		std::cout << "~ ~ ~ ~ ~\n";
	}
}
//prints all pages user follows
void User::showAllFollowedPages()
{
	int size = followedPages.size();
	if (size == 0) //Exceptions
		std::cout << "You're not following any pages at the moment.\n";
	else
	{
		std::cout << name << "'s followed pages: \n";
		std::cout << "~ ~ ~ ~ ~\n";
		std::vector<Page*>::iterator itr = followedPages.begin();
		std::vector<Page*>::iterator end = followedPages.end();

		for (; itr != end; ++itr)
		{
			(*itr)->getName();
			std::cout << "\n";
		}
		std::cout << "~ ~ ~ ~ ~\n";
	}
}
//adds a new page to follow. returns true if succeeds, else returns false.
bool User::addPageToFollowedPages(Page& page, bool noErrMsg)
{
	Page* searchedPage = findPage(page.getName());

	if (searchedPage == nullptr)
	{
		if (followedPages.size() == followedPages.capacity())
			followedPages.reserve(2 * followedPages.capacity());

		followedPages.push_back(&page);
		page.addUserToPageFollowers(*this, true);
		return true;
	}
	else
		if (!noErrMsg) //Meaning, we're not here because of a loop //Exceptions
		{
			std::cout << "You're already following " << page.getName() << "!\n";
			return false;
		}
	return true;
}
//removes a page from followed pages. returns true if succeeds, else returns false.
bool User::removePageFromFollowedPages(Page& page, bool noErrMsg)
{
	std::vector<Page*>::iterator itr = followedPages.begin();
	std::vector<Page*>::iterator itrEnd = followedPages.end();

	for (; itr != itrEnd; ++itr)
	{
		if ((*itr)->getName() == page.getName())
		{
			(*itr) = nullptr;

			std::vector<Page*>::iterator itr2 = itr;

			for (; itr2 != itrEnd; ++itr2)
				itr2 = itr2 + 1;

			followedPages.pop_back();
			page.removeUserFromPageFollowers(*this, true);
			return true;
		}
	}
	if (!noErrMsg) //Meaning, we're not here because of a loop //Exceptions
	{
		std::cout << "You're not following " << page.getName();
		return false;
	}
	return true;
}
//searches array of friends to find a user's name. Returns pointer to user if found, else returns nullptr.
User* User::findFriend(const std::string& name) {

	std::vector<User*>::iterator itr = friendsArr.begin();
	std::vector<User*>::iterator itrEnd = friendsArr.end();

	for (; itr != itrEnd; ++itr)
	{
		if (name == (*itr)->getName())
			return (*itr);
	}
	return nullptr;
}
//searches array of followed pages to find a page's name. Returns pointer to page if found, else returns nullptr.
Page* User::findPage(const std::string& name) {
	std::vector<Page*>::iterator itr = followedPages.begin();
	std::vector<Page*>::iterator itrEnd = followedPages.end();

	for (; itr != itrEnd; ++itr)
	{
		if (name == (*itr)->getName())
			return (*itr);
	}
	return nullptr;
}
//creates a new status for user.
void User::createNewStatus()
{
	std::string text;
	std::cout << "Please type in your status (up to " << MAX_STATUS_LEN << " characters): \n";
	std::cin.ignore();
	getline(std::cin, text);

	setStatus(text);
}
//private func that removes a user from another user's friends list.
void User::unfriendOneSide(User& reqwestedUser)
{
	int amountUsers = friendsArr.size();
	bool isFound = false;

	std::vector<User*>::iterator itr = friendsArr.begin();
	std::vector<User*>::iterator itrEnd = friendsArr.end();

	for (;  itr != itrEnd && !isFound; ++itr)
	{
		if ((*itr)->getName() == reqwestedUser.getName())
		{
			std::vector<User*>::iterator itr2 = itr;

			for (; itr2 != itrEnd; ++itr2)
				itr = itr + 1;

			isFound = true;
		}
	}

	friendsArr.pop_back();
}