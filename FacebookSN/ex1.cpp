#include "ex1.h"
using namespace std;

//****************** MISCELLANEOUS ******************

void checkMemory(void* ptr) {
	if (ptr == nullptr) {
		cout << "Memory allocation failed!";
		exit(1);
	}
}

int getMaxDay(int month) {
	switch (month) {
	case 1:
	case 3:
	case 5:
	case 7:
	case 8:
	case 10:
	case 12:
		return 31;
	case 4:
	case 6:
	case 9:
	case 11:
		return 30;
	case 2:
		return 28;
	}
	//Assuming that the month received is legal.
}

//****************** MANAGE FACEBOOK ******************

void manageSystem(SocialNetwork& system)
{
	int input;
	do
	{
		cout << "Choose an action:\n";

		cout << "1 - Show all existing accounts in the system\n";
		cout << "0 - Return to main menu\n";

		cin >> input;

		switch (input)
		{
		case 0:
			break;
		case 1:
			system.showAllAccounts();
			break;
		default:
			cout << "Invalid choice! Try again! ";
		}
	} while (input != 0);
}

void manageUsers(SocialNetwork& system)
{
	int input;
	do
	{
		if (system.getUsersAmount() == 0)
		{
			cout << "No users exist in the system. Please create a new user: \n";
			input = 1;
		}
		else
		{
			cout << "Choose an action:\n";

			cout << "1 - Sign up (Create a new user)\n";
			cout << "2 - Log in (Choose a user)\n";
			cout << "0 - Return to main menu\n";

			cin >> input;
		}

		User* user;

		switch (input)
		{
		case 0:
			break;
		case 1:
			user = addUser(system);
			userMenu(*user, system);
			break;
		case 2:
			user = findUser(system);
			userMenu(*user, system);
			break;
		default:
			cout << "Invalid choice! Try again! ";
		}
	} while (input != 0);
}

void managePages(SocialNetwork& system)
{
	int input;
	do
	{
		if (system.getPagesAmount() == 0)
		{
			cout << "No pages exist in the system. Please create a new page: \n";
			input = 1;
		}
		else
		{
			cout << "Choose an action:\n";

			cout << "1 - Create a new page\n";
			cout << "2 - Manage existing page\n";
			cout << "0 - Return to main menu\n";

			cin >> input;
		}

		Page* page;

		switch (input)
		{
		case 0:
			break;
		case 1:
			page = addPage(system);
			pageMenu(*page, system);
			break;
		case 2:
			page = findPage(system);
			pageMenu(*page, system);
			break;
		default:
			cout << "Invalid choice! Try again! ";
		}

	} while (input != 0);
}

//****************** MENUS ******************

void userMenu(User& user, SocialNetwork& system)
{
	int input;
	bool success;

	cout << "~X~X Welcome, " << user.getName() << "! X~X~\n";

	do
	{
		cout << "Choose an action:\n";

		cout << "1 - Add a new status\n";
		cout << "2 - Show all of my statuses\n";
		cout << "3 - Show the latest statuses from my friends\n";
		cout << "4 - Send friend request\n";
		cout << "5 - Unfriend a user\n";
		cout << "6 - Follow a new page\n";
		cout << "7 - Unfollow a page\n";
		cout << "8 - Show friends list\n";
		cout << "9 - Show followed pages\n";
		cout << "0 - Log out\n";

		cin >> input;

		switch (input)
		{
		case 0:
			cout << "You logged out of " << user.getName() << ".\n\n";
			break;
		case 1:
			user.createNewStatus();
			cout << "\n" << user.getName() << ", Your new status has been posted!\n\n";
			break;
		case 2:
			user.showAllUserStatuses();
			break;
		case 3:
			if (user.getConnections().logSize == 0)
				cout << "You have no friends!\n";
			else
				user.show10LatestFriendsStatuses();
			break;
		case 4:
			success = sendFriendRequest(user, system);
			if (success)
				cout << "\n" << user.getName() << " has accepted your friend request!\n";
			break;
		case 5:
			if (user.getConnections().logSize == 0)
				cout << "You have no friends!\n";
			else
			{
				unfollowFriend(user);
				cout << "\n" << "You unfriended " << user.getName() << "!\n";
			}
			break;
		case 6:
			followPage(user, system);
			break;
		case 7:
			unfollowPage(user, system);
			break;
		case 8:
			user.showAllFriends();
			break;
		case 9:
			user.showAllFollowedPages();
			break;
		default:
			cout << "Invalid choice! Try again! ";
		}
	} while (input != 0);
}

void pageMenu(Page& page, SocialNetwork& system)
{
	int input;

	cout << "~X~X You are now logged into " << page.getName() << "! X~X~\n";

	do
	{
		cout << "Choose an action:\n";

		cout << "1 - Add a new status\n";
		cout << "2 - Show all of my statuses\n";
		cout << "3 - Add a new follower\n";
		cout << "4 - Remove an existing follower\n";
		cout << "5 - Show followers list\n";
		cout << "0 - Log out\n";

		cin >> input;

		switch (input)
		{
		case 0:
			cout << "You logged out of " << page.getName() << ".\n\n";
			break;
		case 1:
			page.createNewStatus();
			break;
		case 2:
			page.showAllStatuses();
			break;
		case 3:
			addFollowerToPage(page, system);
			break;
		case 4:
			if (page.getFollowers().logSize == 0)
				cout << "You have no followers!\n";
			else
				removeFollowerFromPage(page, system);
			break;
		case 5:
			page.showUsersList();
			break;
		default:
			cout << "Invalid choice! Try again! ";
		}
	} while (input != 0);
}

//****************** USER ACTIONS ******************

User* addUser(SocialNetwork& system) 
{
	char name[MAX_NAME_LEN];
	int day, month, year;
	User* user = nullptr;
	bool legalDOB;

	do 
	{
		cout << "Enter your name (max " << MAX_NAME_LEN << " characters): ";
		cin.ignore();
		cin.getline(name, MAX_NAME_LEN);


		user = system.findUser(name);
		if (user != nullptr)
			cout << "The user " << name << " already exists on Facebook! Please select a different name. \n";
	} while (user != nullptr);

	do {
		cout << "Please enter your date of birth in the following format: <day> <month> <year> \n";
		cin >> day >> month >> year;

		if ((year < 1900 || year > 2022) || (month < 1 || month > 12) || (day < 1 || day > getMaxDay(month))) {
			cout << "Error! Invalid date entered!\n";
			legalDOB = false;
		}
		else
			legalDOB = true;
	} while (!legalDOB);

	return system.setUser(day, month, year, name);
}

User* findUser(SocialNetwork& system) {
	char name[MAX_NAME_LEN];
	User* userPtr;
	cin.ignore(); //Get rid of buffer chars if there are any
	do
	{
		cout << "Choose a user: ";
		cin.getline(name, MAX_NAME_LEN);

 		userPtr = system.findUser(name);

		if (userPtr == nullptr)
			cout << "\nUser not found! Try again!\n";
	} while (userPtr == nullptr);
	return userPtr;
}

bool sendFriendRequest(User& user, SocialNetwork& system) 
{
	char friendName[MAX_NAME_LEN];
	User* friendPtr;
	User* alreadyFriends;
	bool validInput;
	cin.ignore(); //In case of chars in buffer
	do 
	{
		validInput = true;
		cout << "Choose a user to send a friend request to: ";
		cin.getline(friendName, MAX_NAME_LEN);

		friendPtr = system.findUser(friendName);
		if (friendPtr == nullptr) 
		{
			cout << "User not found! Please try again.\n";
			validInput = false;
		}
		
	} while (!validInput);

	return user.friendRequest(*friendPtr);
}

void unfollowFriend(User& user)
{
	char friendName[MAX_NAME_LEN];
	User* friendPtr = nullptr;
	cin.ignore();
	do
	{
		cout << "Choose a user to unfriend: ";
		cin.getline(friendName, MAX_NAME_LEN);

		friendPtr = user.findFriend(friendName);

		if (friendPtr == NULL)
			cout << "User not found in friends list! Please try again.\n";

	} while (friendPtr == nullptr);

	user.unfriend(*friendPtr);
}

//****************** PAGE ACTIONS ******************

Page* addPage(SocialNetwork& system) {
	char name[MAX_NAME_LEN];
	Page* page = nullptr;
	cin.ignore(); //gets chars from buffer
	do 
	{
		cout << "Enter your page's name (max " << MAX_NAME_LEN << " characters): ";
		cin.getline(name, MAX_NAME_LEN);

		page = system.findPage(name);
		if (page != nullptr)
			cout << "The page " << name << "already exists on Facebook! Please select a different name. \n";
	} while (page != nullptr);

	return system.setPage(name);
}

Page* findPage(SocialNetwork& system) {
	char name[MAX_NAME_LEN];
	Page* pagePtr;
	cin.ignore(); //In case of chars in buffer
	do
	{
		cout << "Choose a page: ";
		cin.getline(name, MAX_NAME_LEN);

		pagePtr = system.findPage(name);

		if (pagePtr == nullptr)
			cout << "\nPage not found! Try again!\n";
	} while (pagePtr == nullptr);
	return pagePtr;
}

void followPage(User& user, SocialNetwork& system)
{
	char pageName[MAX_NAME_LEN];
	Page* pagePtr;
	cin.ignore(); //In case of chars in buffer
	do
	{
		cout << "Please enter the page you'd like to follow: ";
		cin.getline(pageName, MAX_NAME_LEN);

		pagePtr = system.findPage(pageName);
		if (pagePtr == nullptr)
			cout << "Page not found! Please try again.\n";

	} while (pagePtr == nullptr);

	if (user.addPageToFollowedPages(*pagePtr))
		cout << "You are now following " << pageName << "!\n";
}

void unfollowPage(User& user, SocialNetwork& system)
{
	if (user.getFollowedPages().logSize == 0)
		cout << "You're not following any pages!\n";
	else
	{
		char pageName[MAX_NAME_LEN];
		Page* pagePtr = nullptr;
		cin.ignore(); //In case of chars in buffer
		do
		{
			cout << "Choose a page to unfollow: ";
			cin.getline(pageName, MAX_NAME_LEN);

			pagePtr = user.findPage(pageName);

			if (pagePtr == NULL)
				cout << "Page not found in followed pages list! Please try again.\n";

		} while (pagePtr == nullptr);

		if (user.removePageFromFollowedPages(*pagePtr))
			cout << "You are no longer following " << pageName << "!\n";
	}
}

void addFollowerToPage(Page& page, SocialNetwork& system) {
	char followerName[MAX_NAME_LEN];
	User* followerPtr = nullptr;
	User* alreadyFollows;
	bool validInput;
	cin.ignore(); //In case of chars in buffer
	do
	{
		validInput = true;
		cout << "Choose a user to follow your page: ";
		cin.getline(followerName, MAX_NAME_LEN);

		followerPtr = system.findUser(followerName);
		if (followerPtr == nullptr) {
			cout << "User not found! Please try again.\n";
			validInput = false;
		}
		alreadyFollows = page.findFollower(followerName);
		if (alreadyFollows != nullptr) {
			cout << followerName << " is already following you! Please try again.\n";
			validInput = false;
		}
	} while (!validInput);

	if (page.addUserToPageFollowers(*followerPtr))
		cout << followerName << " is now following your page!\n";
}

void removeFollowerFromPage(Page& page, SocialNetwork& system)
{
	char followerName[MAX_NAME_LEN];
	User* followerPtr = nullptr;
	cin.ignore(); //gets chars from buffer
	do
	{
		cout << "Choose a user to remove from followers: ";
		cin.getline(followerName, MAX_NAME_LEN);

		followerPtr = page.findFollower(followerName);

		if (followerPtr == NULL)
			cout << "User not found in followers list! Please try again.\n";

	} while (followerPtr == nullptr);

	page.removeUserFromPageFollowers(*followerPtr);

	cout << followerName << " is no longer following your page!\n";
}