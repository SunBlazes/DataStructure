#include "max.h"

int gAll = 12;

static double max(double a, double b) {
	return a > b ? a : b;
}

double useMax(double a, double b) {
	return max(a, b);
}
