#include "Page.h"
using namespace std;

//************************************************************************************

//c'tor 
Page::Page(const string& name)
{
	this->name = name;

}

//********************************************************************************

//get funcs: allows access to the class attributes
const string& Page::getName() const
{
	return name;
}

const vector<User*>& Page::getFollowers() const
{
	return followers;
}

const vector<Status*>& Page::getWall() const
{
	return wall;
}

//***********************************************************************************

//set funcs: insert values into class attributes
void Page::setname(std::string& newName)
{
	name = newName;
}

void Page::setFollowers(User& newFollower)
{
	if (followers.size() == followers.capacity())
		followers.reserve(2 * followers.capacity());

	followers.push_back(&newFollower);
}

void Page::setWall(Status& newStatus)
{
	if (wall.size() == wall.capacity())
		wall.reserve(2 * wall.capacity());
	
	wall.push_back(&newStatus);
}

void Page::setStatus(std::string& text)
{
	Status* newStatus = new Status(text);
	checkMemory(newStatus);

	setWall(*newStatus);
}

//********************************************************************

//methods:

//Shows all statuses of page
void Page::showAllStatuses() 
{
	int size = wall.size();
	if (size == 0) //Exceptions
		std::cout << "You have no statuses on your wall!\n";
	else
	{
		std::cout << "Showing all statuses for page " << name << ":\n";
		std::cout << "~ ~ ~ ~ ~\n\n";

		vector<Status*>::iterator itr = wall.begin();
		vector<Status*>::iterator itrEnd = wall.end();

		for (; itr != itrEnd; ++itr)
		{
			(*itr)->printStatus();
			std::cout << "\n";
		}
		std::cout << "~ ~ ~ ~ ~\n";
	}
}
//adds user to followers of page. When using this function, only send follower.
bool Page::addUserToPageFollowers(User& follower, bool noErrMsg)
{
	User* searchedUser = findFollower(follower.getName());

	if (searchedUser == nullptr)
	{
		if (followers.size() == followers.capacity())
			followers.reserve(2 * followers.capacity());

		followers.push_back(&follower);
		follower.addPageToFollowedPages(*this, true);
		return true;
	}
	else
		if (!noErrMsg) //Meaning, we're not here because of a loop //Exception
		{
			std::cout << follower.getName() << " is already following your page!\n";
			return false;
		}
	return true;
}
//removes user from followers of page. When using this function, only send follower.
bool Page::removeUserFromPageFollowers(User& follower, bool noErrMsg)
{
	vector<User*>::iterator itr = followers.begin();
	vector<User*>::iterator itrEnd = followers.end();

	for (; itr != itrEnd; ++itr)
	{
		if ((*itr)->getName() == follower.getName())
		{
			(*itr) = nullptr;

			vector<User*>::iterator itr2 = itr;

			for (; itr2 != itrEnd; ++itr2)
				itr2 = itr2 + 1;

			followers.pop_back();
			follower.removePageFromFollowedPages(*this, true);
			return true;
		}
	}

	if (!noErrMsg) //Exceptions
	{
		std::cout << follower.getName() << " isn't following your page!\n";
		return false;
	}
	return true;
}
//creates a new status for the page
void Page::createNewStatus()
{
	string text;
	std::cout << "Please type in your status (up to " << MAX_STATUS_LEN << " characters): \n";
	std::cin.ignore();
	getline(std::cin, text);

	setStatus(text);
}
//searches a follower in followers list. Returns pointer to follower if found, else returns nullptr
User* Page::findFollower(const string& name)
{
	vector<User*>::iterator itr = followers.begin();
	vector<User*>::iterator itrEnd = followers.end();

	for (; itr != itrEnd; ++itr)
		if (name == (*itr)->getName())
			return (*itr);

	return nullptr;
}
//prints all followers of page
void Page::showUsersList()
{
	int size = followers.size();
	if (size == 0) //Exceptions
		std::cout << "You have no followers!\n";
	else
	{
		vector<User*>::iterator itr = followers.begin();
		vector<User*>::iterator itrEnd = followers.end();

		std::cout << name << "'s followers: \n";
		std::cout << "~ ~ ~ ~ ~\n";
		for (int i = 0; i < size; i++)
			std::cout << (*itr)->getName() << "\n";
		std::cout << "~ ~ ~ ~ ~\n";
	}
}