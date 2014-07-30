// section 5.7
// ex. 5-8: there is no error checking in day_of_year or month_day. Remedy this
// defect.
#include <stdio.h>

static char daytab[2][13] = {
	{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
	{0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

int day_of_year(int, int, int);
void month_day(int, int, int *, int *);

int main() {
	int year = 2014, month = 7, day = 18;	// july 18th
	int dy = day_of_year(year, month, day);
	printf("%02d/%02d/%4d is day %d of the year\n", month, day, year, dy);
	int yday = 288;
	month_day(year, yday, &month, &day);
	printf("Day %d of the year will fall on %02d/%02d\n", yday, month, day);
	day_of_year(2014, 2, 31);
	month_day(2014, 367, &month, &day);
	return 0;
}

// day_of_year: set day of year from month and day
int day_of_year(int year, int month, int day) {
	int i, leap;

	leap = year%4 == 0 && year%100 != 0 || year%400 == 0;
	if (month > 12 || daytab[leap][month] < day) {
		printf("day_of_year: invalid month/day combination %d/%d\n",
			month, day);
		return -1;
	}
	for (i=1; i<month; ++i)
		day += daytab[leap][i];
	return day;
}

// month_day: set month and day from day of year
void month_day(int year, int yday, int *month, int *day) {
	int i, leap;
	
	leap = year%4 == 0 && year%100 != 0 || year%400 == 0;
	if (yday > 365+leap)
		printf("month_day: invalid year/day combination %d/%d\n",
			year, yday);
	for (i=1; yday > daytab[leap][i]; ++i)
		yday -= daytab[leap][i];
	*month = i;
	*day = yday;
}
