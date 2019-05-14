#include <iostream>
#include <map>
#include <time.h>
#include <cmath>
#include <climits>
#include <omp.h>

using namespace std;

#define PRINT_ALL_PRIMES false

#define PRIME false
#define NOT_PRIME true

enum AlgorithmType {
	SEQUENTIAL,
	OPEN_MP
};

void markMultiples(long long k, bool *numbers, long long n) {
	long long lowerBound = k * k;
	for (long long i = lowerBound; i <= n; i += k) {
		numbers[i] = true;
	}
}

long long getSmallestUnmarkedOver(long long k, bool *numbers, long long n) {
	for (long long i = k + 1; i <= n; i++) {
		if (!numbers[i]) {
			return i;
		}
	}
	cout << "getSmallestUnmarkedOver(): This shouldn't happen" << endl;
	return LLONG_MIN;
}

void printPrimes(bool *numbers, long long n) {
	cout << "Primes until " << n << ":\n";
	for (long long i = 2; i <= n; i++) {
		if (numbers[i] == PRIME) {
			cout << i << ", ";
		}
	}
	cout << "\n";
}

long long countPrimes(bool *numbers, long long n) {
	long long count = 0;
	for (long long i = 2; i <= n; i++) {
		if (numbers[i] == PRIME) {
			count++;
		}
	}
	return count;
}

void sieveParallel(bool* numbers, long long n){
	long long k = 2;
	
	#pragma omp parallel for
	for (long long i = 0; i <= n; i++) {
		numbers[i] = false;
	}

	do {
		long long lowerBound = k * k;
		#pragma omp parallel for
		for (long long i = lowerBound; i <= n; i += k) {
			numbers[i] = true;
		}
		k = getSmallestUnmarkedOver(k, numbers, n);
	} while (k*k <= n);

}

void sieveSequential(bool *numbers, long long n) {
	long long k = 2;
	
	for (long long i = 0; i <= n; i++) {
		numbers[i] = false;
	}
	do {
		markMultiples(k, numbers, n);
		k = getSmallestUnmarkedOver(k, numbers, n);
	} while (k*k <= n);
}

void sieve(long long n, AlgorithmType type) {
	double start, finish;

	bool *numbers = new bool[n + 1]; // includes 0

	start = omp_get_wtime();

	switch (type) {
	case SEQUENTIAL:
		sieveSequential(numbers, n);
		break;
	case OPEN_MP:
		sieveParallel(numbers, n);
		break;
	default:
		throw runtime_error("sieve(): Invalid option");
	}

	finish = omp_get_wtime();

	char st[100];
	sprintf(st, "Time: %3.3f seconds\n",
		finish - start);
	cout << st;
	long long numberPrimes = countPrimes(numbers, n);
	cout << "Number of Primes: "<< numberPrimes <<endl;

#if PRINT_ALL_PRIMES
	printPrimes(numbers, n);
#endif

	delete[] numbers;
}

void printOptions() {
  cout << "Options:\n";
  cout << "1. Sequential\n";
  cout << "2. Parallel - Shared (OpenMP)\n";
}

void executeOption(int option) {
	if (option == 0) {
		throw runtime_error("Exiting");
	}

	int power;
	cout << "Power (2^x): ";
	cin >> power;
	long long n = pow(2, power);
	switch (option) {
	case 1:
		sieve(n, SEQUENTIAL);
		break;
	case 2:
		sieve(n, OPEN_MP);
		break;
	default:
		throw runtime_error("Invalid option");
		break;
	}
}

int main() {
	bool loop = true;
	do {
		printOptions();
		int option;
		cout << "Option: ";
		cin >> option;
		try {
			executeOption(option);
			cout << "\n";
		}
		catch (const exception &e) {
			cerr << e.what() << "\n";
			loop = false;
		}
	} while (loop);
	
	return 0;
}