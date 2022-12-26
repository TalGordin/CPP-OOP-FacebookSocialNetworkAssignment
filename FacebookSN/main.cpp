#include "socialnetwork.h"

void main()
{
	SocialNetwork system;

	system.initializeFaceBookUsers();

	int input;
	std::cout << "Welcome to <FaceBook> (not affiliated with Meta)!\n";

	do
	{
		std::cout << "Please choose an action:\n";

		std::cout << "1 - Manage system\n";
		std::cout << "2 - Manage users\n";
		std::cout << "3 - Manage pages\n";
		std::cout << "0 - Exit\n";

		std::cin >> input;

		switch (input)
		{
		case 0:
			break;
		case 1:
			manageSystem(system);
			break;
		case 2:
			manageUsers(system);
			break;
		case 3:
			managePages(system);
			break;
		default:
			std::cout << "Invalid choice! Try again! ";
		}

	} while (input != 0);
}
