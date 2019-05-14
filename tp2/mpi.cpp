#include <iostream>
#include <cmath>
#include <climits>
#include <mpi.h>

#define PRIME false
#define NOT_PRIME true

#define BLOCK_LOW(i, n, p) ((i) * (n) / (p))
#define BLOCK_HIGH(i, n, p) (BLOCK_LOW((i) + 1, n, p) - 1)
#define BLOCK_SIZE(i, n, p) (BLOCK_LOW((i) + 1, n, p) - BLOCK_LOW(i, n, p))

using namespace std;

bool* newList(unsigned long long n) {
	bool *list = new bool[n * sizeof(bool)];
	fill_n(list, n, PRIME);
	return list;
}

void sieveDistributed(int power) {
	unsigned long long n = pow(2, power);

	MPI_Init(NULL, NULL);

	int numProcesses;
	int processRank;
	bool *list;
	unsigned long long startBlockValue = LLONG_MIN , counter = 0, primes = 0;
	double openMPITime = 0;

	MPI_Comm_rank(MPI_COMM_WORLD, &processRank);
	MPI_Comm_size(MPI_COMM_WORLD, &numProcesses);

	// calculate each block's boundaries
	unsigned long long blockSize = BLOCK_SIZE((unsigned long long) processRank, (unsigned long long) (n - 1), (unsigned long long) numProcesses);
	unsigned long long lowValue = BLOCK_LOW((unsigned long long) processRank, (unsigned long long) (n - 1), (unsigned long long) numProcesses) + 2;
	unsigned long long highValue = BLOCK_HIGH((unsigned long long) processRank, (unsigned long long) (n - 1), (unsigned long long) numProcesses) + 2;

	list = newList(blockSize);

	MPI_Barrier(MPI_COMM_WORLD);

	if (processRank == 0) {
		openMPITime = -MPI_Wtime();
	}

	for (unsigned long long k = 2; k*k <= n;) {
		// calculate the start block value to each process
		if (pow(k, 2) < lowValue) {
			lowValue% k == 0 ?
				startBlockValue = lowValue :
				startBlockValue = lowValue + (k - (lowValue % k));
		} else {
			startBlockValue = pow(k, 2);
		}

		// mark multiples
		for (unsigned long long i = startBlockValue; i <= highValue; i += k)
			list[i - lowValue] = NOT_PRIME;

		// get the next prime to broadcast it to the other processes
		if (processRank == 0) {
			do {
				k++;
			} while (list[k - lowValue] == NOT_PRIME && pow(k, 2) < highValue);
		}

		MPI_Bcast(&k, 1, MPI_LONG, 0, MPI_COMM_WORLD);
	}

	if (processRank == 0) {
		openMPITime += MPI_Wtime();
		cout << "Time: " << openMPITime << "s\n";
	}

	for (unsigned long long i = 0; i < blockSize; i++) {
		if (list[i] == PRIME) {
			counter++;
			//cout << i + lowValue << " is prime\n";
		}
	}

	if (numProcesses > 1) {
		MPI_Reduce(&counter, &primes, 1, MPI_LONG, MPI_SUM, 0, MPI_COMM_WORLD);
	} else {
		primes = counter;
	}

	if (processRank == 0) {
		cout << "Number of primes: " << primes << endl;
	}

	MPI_Finalize();
}

int main(int argc, char **argv) {
	if (argc != 2) {
		cout << "Wrong usage\n";
		return 1;
	}
	int power = atoi(argv[1]);
	sieveDistributed(power);
	return 0;
}