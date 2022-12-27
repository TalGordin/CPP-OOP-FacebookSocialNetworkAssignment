#ifndef _SNExceptions_
#define _SNExceptions_
#include "ex1.h"
using namespace std;
#include <stdexcept>

class SNException : public std::exception
{
public:
	const char* repeatedUsername() { return "The user already exists on Facebook!"; }
	const char* illegalDOB() { return "Error! Invalid date entered!"; }
	const char* userNotFound() { return "Error! User not found!"; }
	const char* repeatedPage() { return "The page already exists on Facebook!"; }
	const char* pageNotFound() { return "Error! Page not found!"; }
	//const char* 
};


#endif // _UserExceptions_
