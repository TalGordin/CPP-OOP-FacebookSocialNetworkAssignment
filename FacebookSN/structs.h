#ifndef _TIME_H
#define _TIME_H

const int MIN_PHY_SIZE = 3;

class User;
class Status;
class Page;
class SocialNetwork;

typedef struct date
{
	int day;
	int month;
	int year;

} Date;

typedef struct time
{
	Date date;
	int hours;
	int minutes;
} Time;

typedef struct usersArr
{
	User** arrOfUsers = nullptr;
	int logSize = 0;
	int phySize = MIN_PHY_SIZE;

} UsersArr;

typedef struct statusesArr
{
	Status** arrOfStatuses = nullptr;
	int logSize = 0;
	int phySize = MIN_PHY_SIZE;

} StatusesArr;

typedef struct pagesArr
{
	Page** arrOfPages = nullptr;
	int logSize = 0;
	int phySize = MIN_PHY_SIZE;

} PagesArr;

struct tm* localtime(const time_t* time);

#endif
