#include <iostream>
#include <map>
#include <time.h>

using namespace std;

#define PRINT_ALL_PRIMES false

enum AlgorithmType {
	SEQUENTIAL,
	OPEN_MP,
	MPI
};

void markMultiples(long long k, bool *numbers, long long n) {
	int lowerBound = k * k;
	for (long long i = lowerBound; i <= n; i += k) {
		numbers[i] = true;
	}
}

int getSmallestUnmarkedOver(long long k, bool *numbers, long long n) {
	for (long long i = k + 1; i <= n; i++) {
		if (!numbers[i]) {
			return i;
		}
	}
	throw exception("getSmallestUnmarkedOver(): This shouldn't happen");
}

void printPrimes(bool *numbers, long long n) {
	cout << "Primes until " << n << ":\n";
	for (long long i = 2; i <= n; i++) {
		if (!numbers[i]) {
			cout << i << ", ";
		}
	}
	cout << "\n";
}

void sieveSequential(bool *numbers, long long n) {
	long long k = 2;
	do {
		markMultiples(k, numbers, n);
		k = getSmallestUnmarkedOver(k, numbers, n);
	} while (k*k <= n);
}

void sieve(long long n, AlgorithmType type) {
	clock_t start, finish;

	bool *numbers = new bool[n + 1]; // includes 0
	for (long long i = 0; i <= n; i++) {
		numbers[i] = false;
	}

	start = clock();

	switch (type) {
	case SEQUENTIAL:
		sieveSequential(numbers, n);
		break;
	case OPEN_MP:
		break;
	case MPI:
		break;
	default:
		throw exception("sieve(): Invalid option");
	}

	finish = clock();

	char st[100];
	sprintf(st, "Time: %3.3f seconds\n",
		(double)(finish - start) / CLOCKS_PER_SEC);
	cout << st;

#if PRINT_ALL_PRIMES
	printPrimes(numbers, n);
#endif

	delete[] numbers;
}

void printOptions() {
  cout << "Options:\n";
  cout << "1. Sequential\n";
  cout << "2. Parallel - Shared (OpenMP)\n";
  cout << "3. Parallel - Distributed (MPI)\n";
}

void executeOption(int option) {
	if (option == 0) {
		throw exception("Exiting");
	}

	long long n;
	cout << "Size: ";
	cin >> n;
	switch (option) {
	case 1:
		sieve(n, SEQUENTIAL);
		break;
	case 2:
		sieve(n, OPEN_MP);
		break;
	case 3:
		sieve(n, MPI);
		break;
	default:
		throw exception("Invalid option");
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