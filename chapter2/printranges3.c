// section 2.2
// ex 2-1: write a program to print the ranges of float, double, and long double variables by calculating limits
#include <stdio.h>
#include <float.h>

unsigned char bits(unsigned short);
float float_min();
float float_max();
double double_min();
double double_max();
long double dlong_min();
long double dlong_max();

int main() {
	printf("Floating point information:\n");
	printf("float radix: %d\n", FLT_RADIX);
	printf("float exponent size: %d (%d bits)\n",
		FLT_MAX_EXP, bits(FLT_MAX_EXP));
	printf("double exponent size: %d (%d bits)\n",
		DBL_MAX_EXP, bits(DBL_MAX_EXP));
	printf("long double exponent size: %d (%d bits)\n",
		LDBL_MAX_EXP, bits(LDBL_MAX_EXP));
	printf("Ranges:\n");
	printf("float: [%f, %f]\n", float_min(), float_max());
	printf("float: [%f, %f] (system)\n", FLT_MIN, FLT_MAX);
	printf("double: [%f, %f]\n", double_min(), double_max());
	printf("double: [%f, %f] (system)\n", DBL_MIN, DBL_MAX);
	printf("long double: [%Lf, %Lf]\n", dlong_min(), dlong_max());
	printf("long double: [%Lf, %Lf] (system)\n", LDBL_MIN, LDBL_MAX);
	return 0;
}

unsigned char bits(unsigned short val) {
	unsigned char v = 0;
	for (v=0; val != 0; v++)
		val >>= 1;
	return v;
}

// two: fills mantissa of float
float float_two() {
	float f = 0, b = 1, last = 0;
	while (f != 2.0) {
		last = f;
		f += 1 / b;
		b *= 2;
	}
	return last;
}

float float_min() {
	float mant = float_two();
	float last = mant;
	while (last != 0.0) {
		mant = last;
		last /= 2;
	}
	return mant;
}

float float_max() {
	float mant = float_two();
	float last = mant*2;
	while (last/mant == 2.0) {
		mant = last;
		last *= 2;
	}
	return mant;
}

double double_two() {
	double f = 0, b = 1, last = 0;
	while (f != 2.0) {
		last = f;
		f += 1 / b;
		b *= 2;
	}
	return last;
}

double double_min() {
	double mant = double_two();
	double last = mant;
	while (last != 0.0) {
		mant = last;
		last /= 2;
	}
	return mant;
}

double double_max() {
	double mant = double_two();
	double last = mant*2;
	while (last/mant == 2.0) {
		mant = last;
		last *= 2;
	}
	return mant;
}

long double dlong_two() {
	long double f = 0, b = 1, last = 0;
	while (f != 2.0) {
		last = f;
		f += 1 / b;
		b *= 2;
	}
	return last;
}

long double dlong_min() {
	long double mant = dlong_two();
	long double last = mant;
	while (last != 0.0) {
		mant = last;
		last /= 2;
	}
	return mant;
}

long double dlong_max() {
	long double mant = dlong_two();
	long double last = mant*2;
	while (last/mant == 2.0) {
		mant = last;
		last *= 2;
	}
	return mant;
}
