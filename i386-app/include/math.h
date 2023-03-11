#pragma once

// declaration of constants.
const double PI          = 3.141592653589793;
const double HALF_PI     = 1.570796326794897;
const double DOUBLE_PI   = 6.283185307179586;
const double SIN_CURVE_A = 0.0415896;
const double SIN_CURVE_B = 0.00129810625032;

//structure of a two-dimensional vector of integers.
struct vec2i {
	int x, y;
};

//structure of a three-dimensional vector of integers.
struct vec3i {
	int x, y;
};

//structure of a two-dimensional vector of rational numbers.
struct vec2f {
	float x, y;
};

//structure of a three-dimensional vector of rational numbers.
struct vec3f {
	float x, y;
};

//function to find the absolute value of an integer.
//#define abs(x) (if(x<0) -x; x)
int abs(int x) {
	if(x < 0)
		return -x;
	return x;
}

int sgn(int x) {  //function to find the sign of an integer.
	if(x < 0)
		return -1;
	return 1;
}

float sqrt(float number) {  //function to find the square root of a rational number.
    int start = 0, end = number;
    int mid;
    float ans;
    while (start <= end) {
        mid = (start + end) / 2;
        if (mid * mid == number) {
            ans = mid;
            break;
        }
        if (mid * mid < number) {
            ans=start;
            start = mid + 1;
        }
        else {
            end = mid - 1;
        }
    }
    float increment = 0.1;
	int i;
    for (i = 0; i < 5; i++) {
        while (ans * ans <= number) {
            ans += increment;
        }
        ans = ans - increment;
        increment = increment / 10;
    }
    return ans;
}

//function to compute the power of a given base with a given exponent.
int pow(int base, int exponent) {
    int result = 1;
    for (;;) {
		if (exponent & 1)
			result *= base;
		exponent >>= 1;
		if (!exponent)
			break;
		base *= base;
	}
	return result;
}

//function for calculating the cos.
double cos(double x) {
    if (x < 0) {
        int q = -x / DOUBLE_PI;
		q += 1;
        double y = q * DOUBLE_PI;
        x = -(x - y);
    }
    if (x >= DOUBLE_PI) {
        int q = x / DOUBLE_PI;
        double y = q * DOUBLE_PI;
        x = x - y;
    }
    int s = 1;
    if (x >= PI) {
        s = -1;
        x -= PI;
    }
    if (x > HALF_PI) {
        x = PI - x;
        s = -s;
    }
    double z = x * x;
    double r = z * (z * (SIN_CURVE_A - SIN_CURVE_B * z) - 0.5) + 1.0;
    if (r > 1.0) r = r - 2.0;
    if (s > 0) return r;
    else return -r;
}

//sin calculation function.
double sin(double x) {
    return cos(x - HALF_PI);
}