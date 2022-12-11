#include "socialnetwork.h"
using namespace std;

void main()
{
	SocialNetwork system;

	system.initializeFaceBookUsers();

	int input;
	cout << "Welcome to <FaceBook> (not affiliated with Meta)!\n";

	do
	{
		cout << "Please choose an action:\n";

		cout << "1 - Manage system\n";
		cout << "2 - Manage users\n";
		cout << "3 - Manage pages\n";
		cout << "0 - Exit\n";

		cin >> input;

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
			cout << "Invalid choice! Try again! ";
		}

	} while (input != 0);
}
