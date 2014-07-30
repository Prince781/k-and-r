// section 1.8
#include <stdio.h>

/* print Fahrenheit-Celsius table */
// demo: function

float fahr_to_celsius(float);

int main() {
	float fahr;
	
	for (fahr = 300; fahr >= 0; fahr -= 20)
		printf("%3.0f F = %6.1f C\n", fahr, fahr_to_celsius(fahr));

	return 0;
}

float fahr_to_celsius(float fahr) {
	return 5.0/9.0 * (fahr-32);
}
