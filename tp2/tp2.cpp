#include "lu_factor.hpp"
#include "sieve_erosth.hpp"

#include <iostream>

using namespace std;

void printOptions() {
  cout << "Options:\n";
  cout << "1. LU Factorization - Sequential\n";
}

void executeOption(int option) {

}

int main() {
  printOptions();
  int option;
  cin >> option;
  executeOption(option);
  return 0;
}