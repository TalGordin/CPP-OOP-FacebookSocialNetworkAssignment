#include "Page.h"
using namespace std;

//************************************************************************************

//c'tor 
Page::Page(const string& name)
{
	this->name = name;
}
//Copy c'tor
Page::Page(const Page& copiedPage)
{
	this->name = copiedPage.getName();
	this->followers = copiedPage.getFollowers();
	
	vector<Status*> oldStatuses = copiedPage.getWall();

	vector<Status*>::iterator itr = oldStatuses.begin();
	vector<Status*>::iterator itrEnd = oldStatuses.end();

	for (; itr != itrEnd; ++itr)
	{
		Status* temp = new Status((*itr)->getStatus());
		wall.push_back(temp);
	}
}

Page::Page(const Page&& other) noexcept(true)
{
	this->name = other.getName();
	this->followers = other.getFollowers();

	this->wall = other.getWall();
}

Page::~Page()
{
	vector<Status*>::iterator itr = wall.begin();
	vector<Status*>::iterator itrEnd = wall.end();

	for (; itr != itrEnd; ++itr)
		delete (*itr);
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

const Page& Page::operator+=(User& user)
{
	addUserToPageFollowers(user);
		return *this;
}

const bool Page::operator>(Page& other)
{
	vector<User*> otherFollowers = other.getFollowers();
	return followers.size() > otherFollowers.size() ? true : false;
}


//Shows all statuses of page
void Page::showAllStatuses() noexcept(false)
{
	int size = wall.size();

	if (size == 0)
	{
		try
		{
			throw PageException_FollowerNotFound();
		}
		catch (PageException_FollowerNotFound& exc)
		{
			cout << exc.followerNotFound() << endl;
		}
	}
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
bool Page::addUserToPageFollowers(User& follower, bool noErrMsg) noexcept(false)
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
		 //Meaning, we're not here because of a loop //Exception
		try
		{
			if (!noErrMsg)
				throw PageException_UserAlreadyFollows();
		}
		catch (PageException_UserAlreadyFollows& exc)
		{
			cout << exc.userAlreadyFollows() << endl;
			return false;
		}
	return true;
}
//removes user from followers of page. When using this function, only send follower.
bool Page::removeUserFromPageFollowers(User& follower, bool noErrMsg) noexcept(false)
{
	vector<User*>::iterator itr = followers.begin();
	vector<User*>::iterator itrEnd = followers.end();

	for (; itr != itrEnd; ++itr)
	{
		if ((*itr)->getName() == follower.getName())
		{
			(*itr) = nullptr;

			vector<User*>::iterator itr2 = itr;
			vector<User*>::iterator itr2End = itrEnd - 1;

			for (; itr2 != itr2End; ++itr2)
				*(itr2) = *(itr2 + 1);

			followers.pop_back();
			follower.removePageFromFollowedPages(*this, true);
			return true;
		}
	}

	try
	{
		if (!noErrMsg)
			throw PageException_FollowerNotFound();
	}
	catch (PageException_FollowerNotFound& exc)
	{
		cout << exc.followerNotFound() << endl;
		return false;
	}
	return true;
}
//creates a new status for the page
void Page::createNewStatus()
{
	string text;
	std::cout << "Please type in your status: \n";
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
void Page::showUsersList() noexcept(false)
{
	int size = followers.size();
	if (size == 0)
		try
		{
			throw PageException_NoFollowers();
		}
		catch(PageException_NoFollowers& exc)
		{
			cout << exc.noFollowers() << endl;
		}
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