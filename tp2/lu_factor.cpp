#include <stdexcept>
#include "lu_factor.hpp"

class LUFactor {
private:
	void sequential(int size, double *orig, double *l, double *u) {
		
	}

public:
	double exec(LUFactorType type, int size) {
		double *orig, *l, *u;
		orig = new double[size * size];
		l = new double[size * size];
		u = new double[size * size];

		switch (type) {
		case SEQUENTIAL:
			sequential(size, orig, l, u);
		default:
			throw std::runtime_error("Invalid LU Factor type\n");
		}

		delete[] orig;
		delete[] l;
		delete[] u;
	}
};