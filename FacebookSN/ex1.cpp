#include "ex1.h"

//****************** MISCELLANEOUS ******************

void checkMemory(void* ptr) {
	if (ptr == nullptr) {
		std::cout << "Memory allocation failed!";
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
		std::cout << "Choose an action:\n";

		std::cout << "1 - Show all existing accounts in the system\n";
		std::cout << "0 - Return to main menu\n";

		std::cin >> input;

		switch (input)
		{
		case 0:
			break;
		case 1:
			system.showAllAccounts();
			break;
		default:
			std::cout << "Invalid choice! Try again! ";
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
			std::cout << "No users exist in the system. Please create a new user: \n";
			input = 1;
		}
		else
		{
			std::cout << "Choose an action:\n";

			std::cout << "1 - Sign up (Create a new user)\n";
			std::cout << "2 - Log in (Choose a user)\n";
			std::cout << "0 - Return to main menu\n";

			std::cin >> input;
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
			std::cout << "Invalid choice! Try again! ";
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
			std::cout << "No pages exist in the system. Please create a new page: \n";
			input = 1;
		}
		else
		{
			std::cout << "Choose an action:\n";

			std::cout << "1 - Create a new page\n";
			std::cout << "2 - Manage existing page\n";
			std::cout << "0 - Return to main menu\n";

			std::cin >> input;
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
			std::cout << "Invalid choice! Try again! ";
		}

	} while (input != 0);
}

//****************** MENUS ******************

void userMenu(User& user, SocialNetwork& system)
{
	int input;
	bool success;

	std::cout << "~X~X Welcome, " << user.getName() << "! X~X~\n";

	do
	{
		std::cout << "Choose an action:\n";

		std::cout << "1 - Add a new status\n";
		std::cout << "2 - Show all of my statuses\n";
		std::cout << "3 - Show the latest statuses from my friends\n";
		std::cout << "4 - Send friend request\n";
		std::cout << "5 - Unfriend a user\n";
		std::cout << "6 - Follow a new page\n";
		std::cout << "7 - Unfollow a page\n";
		std::cout << "8 - Show friends list\n";
		std::cout << "9 - Show followed pages\n";
		std::cout << "0 - Log out\n";

		std::cin >> input;

		switch (input)
		{
		case 0:
			std::cout << "You logged out of " << user.getName() << ".\n\n";
			break;
		case 1:
			user.createNewStatus();
			std::cout << "\n" << user.getName() << ", Your new status has been posted!\n\n";
			break;
		case 2:
			user.showAllUserStatuses();
			break;
		case 3:
			if (user.getConnections().size() == 0)
				std::cout << "You have no friends!\n";
			else
				user.show10LatestFriendsStatuses();
			break;
		case 4:
			success = sendFriendRequest(user, system);
			if (success)
				std::cout << "\n" << user.getName() << " has accepted your friend request!\n";
			break;
		case 5:
			if (user.getConnections().size() == 0)
				std::cout << "You have no friends!\n";
			else
			{
				unfollowFriend(user);
				std::cout << "\n" << "You unfriended " << user.getName() << "!\n";
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
			std::cout << "Invalid choice! Try again! ";
		}
	} while (input != 0);
}

void pageMenu(Page& page, SocialNetwork& system)
{
	int input;

	std::cout << "~X~X You are now logged into " << page.getName() << "! X~X~\n";

	do
	{
		std::cout << "Choose an action:\n";

		std::cout << "1 - Add a new status\n";
		std::cout << "2 - Show all of my statuses\n";
		std::cout << "3 - Add a new follower\n";
		std::cout << "4 - Remove an existing follower\n";
		std::cout << "5 - Show followers list\n";
		std::cout << "0 - Log out\n";

		std::cin >> input;

		switch (input)
		{
		case 0:
			std::cout << "You logged out of " << page.getName() << ".\n\n";
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
			if (page.getFollowers().size() == 0)
				std::cout << "You have no followers!\n";
			else
				removeFollowerFromPage(page, system);
			break;
		case 5:
			page.showUsersList();
			break;
		default:
			std::cout << "Invalid choice! Try again! ";
		}
	} while (input != 0);
}

//****************** USER ACTIONS ******************

User* addUser(SocialNetwork& system) 
{
	string name;
	int day, month, year;
	User* user = nullptr;
	bool legalDOB;

	do 
	{
		std::cout << "Enter your name (max " << MAX_NAME_LEN << " characters): ";
		std::cin.ignore();
		getline(std::cin, name);


		user = system.findUser(name);
		if (user != nullptr)
			std::cout << "The user " << name << " already exists on Facebook! Please select a different name. \n";
	} while (user != nullptr);

	do {
		std::cout << "Please enter your date of birth in the following format: <day> <month> <year> \n";
		std::cin >> day >> month >> year;

		if ((year < 1900 || year > 2022) || (month < 1 || month > 12) || (day < 1 || day > getMaxDay(month))) {
			std::cout << "Error! Invalid date entered!\n";
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
	std::cin.ignore(); //Get rid of buffer chars if there are any
	do
	{
		std::cout << "Choose a user: ";
		std::cin.getline(name, MAX_NAME_LEN);

 		userPtr = system.findUser(name);

		if (userPtr == nullptr)
			std::cout << "\nUser not found! Try again!\n";
	} while (userPtr == nullptr);
	return userPtr;
}

bool sendFriendRequest(User& user, SocialNetwork& system) 
{
	char friendName[MAX_NAME_LEN];
	User* friendPtr;
	User* alreadyFriends;
	bool validInput;
	std::cin.ignore(); //In case of chars in buffer
	do 
	{
		validInput = true;
		std::cout << "Choose a user to send a friend request to: ";
		std::cin.getline(friendName, MAX_NAME_LEN);

		friendPtr = system.findUser(friendName);
		if (friendPtr == nullptr) 
		{
			std::cout << "User not found! Please try again.\n";
			validInput = false;
		}
		
	} while (!validInput);

	return user.friendRequest(*friendPtr);
}

void unfollowFriend(User& user)
{
	char friendName[MAX_NAME_LEN];
	User* friendPtr = nullptr;
	std::cin.ignore();
	do
	{
		std::cout << "Choose a user to unfriend: ";
		std::cin.getline(friendName, MAX_NAME_LEN);

		friendPtr = user.findFriend(friendName);

		if (friendPtr == NULL)
			std::cout << "User not found in friends list! Please try again.\n";

	} while (friendPtr == nullptr);

	user.unfriend(*friendPtr);
}

//****************** PAGE ACTIONS ******************

Page* addPage(SocialNetwork& system) {
	char name[MAX_NAME_LEN];
	Page* page = nullptr;
	std::cin.ignore(); //gets chars from buffer
	do 
	{
		std::cout << "Enter your page's name (max " << MAX_NAME_LEN << " characters): ";
		std::cin.getline(name, MAX_NAME_LEN);

		page = system.findPage(name);
		if (page != nullptr)
			std::cout << "The page " << name << "already exists on Facebook! Please select a different name. \n";
	} while (page != nullptr);

	return system.setPage(name);
}

Page* findPage(SocialNetwork& system) {
	char name[MAX_NAME_LEN];
	Page* pagePtr;
	std::cin.ignore(); //In case of chars in buffer
	do
	{
		std::cout << "Choose a page: ";
		std::cin.getline(name, MAX_NAME_LEN);

		pagePtr = system.findPage(name);

		if (pagePtr == nullptr)
			std::cout << "\nPage not found! Try again!\n";
	} while (pagePtr == nullptr);
	return pagePtr;
}

void followPage(User& user, SocialNetwork& system)
{
	char pageName[MAX_NAME_LEN];
	Page* pagePtr;
	std::cin.ignore(); //In case of chars in buffer
	do
	{
		std::cout << "Please enter the page you'd like to follow: ";
		std::cin.getline(pageName, MAX_NAME_LEN);

		pagePtr = system.findPage(pageName);
		if (pagePtr == nullptr)
			std::cout << "Page not found! Please try again.\n";

	} while (pagePtr == nullptr);

	if (user.addPageToFollowedPages(*pagePtr))
		std::cout << "You are now following " << pageName << "!\n";
}

void unfollowPage(User& user, SocialNetwork& system)
{
	if (user.getFollowedPages().size() == 0)
		std::cout << "You're not following any pages!\n";
	else
	{
		char pageName[MAX_NAME_LEN];
		Page* pagePtr = nullptr;
		std::cin.ignore(); //In case of chars in buffer
		do
		{
			std::cout << "Choose a page to unfollow: ";
			std::cin.getline(pageName, MAX_NAME_LEN);

			pagePtr = user.findPage(pageName);

			if (pagePtr == NULL)
				std::cout << "Page not found in followed pages list! Please try again.\n";

		} while (pagePtr == nullptr);

		if (user.removePageFromFollowedPages(*pagePtr))
			std::cout << "You are no longer following " << pageName << "!\n";
	}
}

void addFollowerToPage(Page& page, SocialNetwork& system) {
	char followerName[MAX_NAME_LEN];
	User* followerPtr = nullptr;
	User* alreadyFollows;
	bool validInput;
	std::cin.ignore(); //In case of chars in buffer
	do
	{
		validInput = true;
		std::cout << "Choose a user to follow your page: ";
		std::cin.getline(followerName, MAX_NAME_LEN);

		followerPtr = system.findUser(followerName);
		if (followerPtr == nullptr) {
			std::cout << "User not found! Please try again.\n";
			validInput = false;
		}
		alreadyFollows = page.findFollower(followerName);
		if (alreadyFollows != nullptr) {
			std::cout << followerName << " is already following you! Please try again.\n";
			validInput = false;
		}
	} while (!validInput);

	if (page.addUserToPageFollowers(*followerPtr))
		std::cout << followerName << " is now following your page!\n";
}

void removeFollowerFromPage(Page& page, SocialNetwork& system)
{
	char followerName[MAX_NAME_LEN];
	User* followerPtr = nullptr;
	std::cin.ignore(); //gets chars from buffer
	do
	{
		std::cout << "Choose a user to remove from followers: ";
		std::cin.getline(followerName, MAX_NAME_LEN);

		followerPtr = page.findFollower(followerName);

		if (followerPtr == NULL)
			std::cout << "User not found in followers list! Please try again.\n";

	} while (followerPtr == nullptr);

	page.removeUserFromPageFollowers(*followerPtr);

	std::cout << followerName << " is no longer following your page!\n";
}