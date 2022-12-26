#ifdef _UserExeptions_
#define _UserExeptions_
#include "ex1.h"
using namespace std;

class UserExceptions :: public std::exception
{
private:
	UserExceptions() = defult;
public:
	virtual const char* what() const 
};

#endif // _UserExeptions

