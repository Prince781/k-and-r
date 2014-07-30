// section 1.3
// ex 1-5: modify this program to print the table in reverse order, from 300 degrees to 0
#include <stdio.h>

/* print Fahrenheit-Celsius table */

main()
{
	int fahr;
	
	for (fahr = 300; fahr >= 0; fahr -= 20)
		printf("%3d %6.1f\n", fahr, (5.0/9.0)*(fahr-32));
}
