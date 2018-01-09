#include "types.h"  // this file has all the datatypes
#include "user.h"   // this file has the prototypes of all the system calls
#include "date.h"   // this file contains definition of struct rtcdate

// prototypes of all the functions used
long long power(int,int);
int check_leap(int);
void month_name(int);
void day_name(int,int,int);
void time(void);
void yesterday(void);
void today(void);
void tomorrow(void);
void particular_day(char *);
void utc_day(void);
void day(char *);

// main
int main(int argc, char *argv[])
{
	// if user only types date in the command prompt
	if(argc==1)
		today();  // this function prints today's date and current time (IST format)
	else
	{
		// if user uses -d option with the date command
		if((argc==3)&&(strcmp("-d",*(argv+1))==0))
			day(*(argv+2));  // this function checks which option is chosen by user
					 // it then calls a suitable function to implement that option

		// if user uses -u option
		else if((argc==2)&&(strcmp("-u",*(argv+1))==0))
			utc_day();  // this function prints today's date and current time (UTC format)

		// if the user types an invalid command
		else
			printf(1,"Invalid command. Please try again.\n");
	}
exit();
}

// this function calculate a power b
long long power(int x,int y)
{
	long long res = 1;
	for(int i=0;i<y;i++)
	{
		res = res * x;
	}
	return(res);
}

// this function whether the current year is a leap year
int check_leap(int x)
{
	int flag = 0;
	if(x%400==0)
		flag = 1;
	else if(x%100==0)
		flag = 0;
	else if(x%4==0)
		flag = 1;
	else 
		flag = 0;
	return(flag);
}

// this function prints the name of the month of the year
void month_name(int x)
{
	switch(x)
	{
		case 1:printf(1," Jan");
		       break;
		case 2:printf(1," Feb");
		       break;
		case 3:printf(1," Mar");
		       break;
		case 4:printf(1," Apr");
		       break;
		case 5:printf(1," May");
		       break;
		case 6:printf(1," Jun");
		       break;
		case 7:printf(1," Jul");
		       break;
		case 8:printf(1," Aug");
		       break;
		case 9:printf(1," Sep");
		       break;
		case 10:printf(1," Oct");
		       break;
		case 11:printf(1," Nov");
		       break;
		case 12:printf(1," Dec");
		       break;
	}
}

// this function prints the name of the day of the week
void day_name(int x,int y,int z)
{
	int initial_day = 4;
	int count = 0;	
	if(x>1970)
	{
		for(int i=1970;i<x;i++)
		{
			if(check_leap(i))
				count += 366;
			else
				count += 365;
		}
	}
	for(int i=1;i<y;i++)
	{
		if(i==2)
		{
			if(check_leap(x))
				count += 29;
			else
				count += 28;
		}
		else if((i<8)&&(i%2==1))
			count += 31;
		else if((i<8)&&(i%2==0))
			count += 30;
		else if((i>=8)&&(i%2==0))
			count += 31;
		else
			count += 30;
	}
	int final_day = (initial_day+count+z-1)%7;
	switch(final_day)
	{
		case 0:printf(1,"Sun");
		       break;
		case 1:printf(1,"Mon");
		       break;
		case 2:printf(1,"Tue");
		       break;
		case 3:printf(1,"Wed");
		       break;
		case 4:printf(1,"Thur");
		       break;
		case 5:printf(1,"Fri");
		       break;
		case 6:printf(1,"Sat");
		       break;
	 }
}

// this function prints the current time in IST format
void time()
{
	struct rtcdate r;
	if (date(&r)) 
	{
		printf(2, "date failed\n");
		exit();
	}
	if(r.minute+30>59)
	{
		r.hour += 6;
		r.minute = r.minute+30-59;
	}
	else
	{
		r.hour += 5;
		r.minute += 30;
	}
	if(r.hour>=24)
		r.hour -= 24;
	printf(1," %d:%d:%d",r.hour,r.minute,r.second);
}

void yesterday()
{
	struct rtcdate r;
	if (date(&r)) 
	{
		printf(2, "date failed\n");
		exit();
	}

	// if month is march
	if(r.month == 3)
	{
		if(check_leap(r.year))
		{
			if(r.day==1)
			{
				r.month -= 1;
				r.day = 29;
			}
			else
				r.day -= 1;
		}
		else
		{
			if(r.day==1)
			{
				r.month -= 1;
				r.day = 28;
			}
			else
				r.day -= 1;
		}
	}

	// if date is 1st Jan
	else if((r.day==1)&&(r.month==1))
	{
		r.month = 12;
		r.day = 31;
		r.year -= 1;
	}

	else
	{
		if(r.month<9)
		{
			if(r.month%2==0)
			{
				if(r.day==1)
				{
					r.month -= 1;
					r.day = 31;
				}
				else
					r.day -= 1;
			}
			else
			{
				if(r.day==1)
				{
					r.month -= 1;
					r.day = 30;
				}
				else
					r.day -= 1;
			}
		}
		else
		{
			if(r.month%2==1)
			{
				if(r.day==1)
				{
					r.month -= 1;
					r.day = 31;
				}
				else
					r.day -= 1;
			}
			else
			{
				if(r.day==1)
				{
					r.month -= 1;
					r.day = 30;
				}
				else
					r.day -= 1;
			}
		}
	}
	day_name(r.year,r.month,r.day);  // prints the name of yesterday's day of the week
	month_name(r.month);  // prints the name of the yesterday's month of the year
	printf(1," %d",r.day);  // prints yesterday's date
	time();  // prints the current time (IST format)
	printf(1," IST");
	printf(1," %d\n",r.year);  // prints yesterday's year
}
	     
// this function prints today's date and current time (IST format)
void today()
{
	struct rtcdate r;
	if (date(&r)) 
	{
		printf(2, "date failed\n");
		exit();
	}
	day_name(r.year,r.month,r.day);	 // prints the name of day of the week
	month_name(r.month);  // prints the name of the month of the year
	printf(1," %d",r.day);  // prints the today's date
	time();  // prints the current time (IST format)
	printf(1," IST");
	printf(1," %d\n",r.year);  // prints the current year
}

// this function prints tomorrow's date and time (IST format)
void tomorrow()
{
	struct rtcdate r;
	if (date(&r)) 
	{
		printf(2, "date failed\n");
		exit();
	}

	// if month is Feb
	if(r.month == 2)
	{
		if(check_leap(r.year))
		{
			if(r.day==29)
			{
				r.month += 1;
				r.day = 1;
			}
			else
				r.day += 1;
		}
		else
		{
			if(r.day==28)
			{
				r.month += 1;
				r.day = 1;
			}
			else
				r.day += 1;
		}
	}

	// if the date is 31st Dec
	else if((r.day==31)&&(r.month==12))
	{
		r.month = 1;
		r.day = 1;
		r.year += 1;
	}

	else
	{
		if(r.month<8)
		{
			if(r.month%2==1)
			{
				if(r.day==31)
				{
					r.month += 1;
					r.day = 1;
				}
				else
					r.day += 1;
			}
			else
			{
				if(r.day==30)
				{
					r.month += 1;
					r.day = 1;
				}
				else
					r.day += 1;
			}
		}
		else
		{
			if(r.month%2==1)
			{
				if(r.day==30)
				{
					r.month += 1;
					r.day = 1;
				}
				else
					r.day += 1;
			}
			else
			{
				if(r.day==31)
				{
					r.month += 1;
					r.day = 1;
				}
				else
					r.day += 1;
			}
		}
	}
	day_name(r.year,r.month,r.day);  // prints the name of tomorrow's day of the week
	month_name(r.month);  // prints the name of the tomorrow's month of the year
	printf(1," %d",r.day);  // prints tomorrow's date
	time();  // prints the current time (IST format)
	printf(1," IST");
	printf(1," %d\n",r.year);  // prints tomorrow's year
}

// if user uses -d option with a particular date
void particular_day(char *x)
{
	int flag = 1;
	for(int i=0;i<4;i++)
	{
		if(*(x+i)=='-')
		{
			flag = 0;
			break;
		}
	}
	for(int i=5;i<7;i++)
	{
		if(*(x+i)=='-')
		{
			flag = 0;
			break;
		}
	}
	for(int i=8;i<10;i++)
	{
		if(*(x+i)=='-')
		{
			flag = 0;
			break;
		}
	}
	if(flag==0)
	{
		printf(1,"date: invalid date %s\n",x);
		exit();
	}
	int y=0;
	int m=0;
	int d=0;
	for(int i=0;i<4;i++)
	{
		y += (*(x+i) - '0')*power(10,3-i);
	}
	for(int i=5;i<7;i++)
	{
		m += (*(x+i) - '0')*power(10,6-i);
	}
	for(int i=8;i<10;i++)
	{
		d += (*(x+i) - '0')*power(10,9-i);
	}	
	if((m>12)||(d>31)||(m<1)||(d<1)||(y<1970))
	{
		printf(1,"date: invalid date %s\n",x);
		exit();
	}	
	else if(m==2)
	{
		if(d>28)
		{
			if(check_leap(y))
			{
				if(d>29)
				{
					printf(1,"date: invalid date %s\n",x);
					exit();
				}
			}
			else
			{
				printf(1,"date: invalid date %s\n",x);
					exit();
			}
		}
	}			
	day_name(y,m,d);
	month_name(m);
	printf(1," %d",d);
	printf(1," 00:00:00 IST");
	printf(1," %d\n",y);
}	

// this function prints today's date and current time (UTC format)
void utc_day()
{
	struct rtcdate r;
	if (date(&r)) 
	{
		printf(2, "date failed\n");
		exit();
	}
	day_name(r.year,r.month,r.day);	 // prints the name of today's day of the week
	month_name(r.month);  // prints the name of the today's month of the year
	printf(1," %d",r.day);  // prints today's date
	printf(1," %d:%d:%d",r.hour,r.minute,r.second);  // prints the current time (UTC format)
	printf(1," UTC");
	printf(1," %d\n",r.year);  // prints current year
}
	
// this function checks which option is chosen by user
// it then calls a suitable function to implement that option
void day(char *x)
{
	switch(*(x+2))
	{
		case 'd':
		case 'w':today();
		         break;
		case 'm':tomorrow();
		         break;
		case 's':yesterday();
		         break;
		default:particular_day(x);
			  break;
	}
}
