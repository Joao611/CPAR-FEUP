#include "lu_factor.hpp"
#include "sieve_erosth.hpp"

#include <iostream>
#include <map>

using namespace std;

void printOptions() {
  cout << "Options:\n";
  cout << "1. LU Factorization - Sequential\n";
}

int executeOption(int option) {
	switch (option) {
	case 1:
		luFactorSeq();
	default:
		cout << "Invalid option\n";
		return -1;
	}

	return 0;
}

int main() {
	int res = 0;
	do {
		printOptions();
		int option;
		cin >> option;
		res = executeOption(option);
	} while (res != 0);
	
	return 0;
}