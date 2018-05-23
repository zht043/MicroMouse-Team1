#include "HelperMethods.h"

double f_abs(double a) {
	return a < 0 ? -a : a;
}
uint8_t f_equal(double x, double y, double errorRange) {
    if(f_abs(x-y) < errorRange) return 1;
    else return 0;
}