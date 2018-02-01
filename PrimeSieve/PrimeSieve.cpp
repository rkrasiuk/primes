// SievePrimes.cpp
#include<iostream>
#include<iomanip>
#include<locale>
#include<vector>
using namespace std;
#include <Windows.h>

double elapsed_time(LARGE_INTEGER const& start, LARGE_INTEGER const& stop, LARGE_INTEGER const& frequency) {
	return double(stop.QuadPart - start.QuadPart) / frequency.QuadPart;
}


using prime_type = unsigned long long;
prime_type constexpr MAX_TEST = 1'000'000'000;

int main() {
	cout.imbue(locale(""));
	cout << "SievePrimes\n";
	cout << "Search [2.." << MAX_TEST << "] for prime numbers.\n";

	// Get window's time
	LARGE_INTEGER timerFrequency;
	QueryPerformanceFrequency(&timerFrequency);

	LARGE_INTEGER startTime, stopTime;
	LARGE_INTEGER& startLoad = startTime, stopLoad;
	LARGE_INTEGER &startSieve = stopLoad, stopSieve;
	LARGE_INTEGER &startCleanup = stopSieve, &stopCleanup = stopTime;

	// find primes
	//...Load
	QueryPerformanceCounter(&startTime);
	vector<bool> primes(MAX_TEST + 1); // defaults each value to 'false' 
	primes[2] = true;
	for (prime_type i = 3; i <= MAX_TEST; ++i)
		primes[i] = true;

	//... Sieve
	QueryPerformanceCounter(&startSieve);
	bool constexpr MARKED = false;
	for (size_t primeValue = 3; primeValue < primes.size(); primeValue += 2) {
		if (primes[primeValue] == MARKED)
			continue;

		for (size_t iMultiple = primeValue + primeValue; iMultiple < primes.size(); iMultiple += primeValue)
			primes[iMultiple] = MARKED;
	}
	//...Cleanup
	QueryPerformanceCounter(&startCleanup);

	vector<prime_type> primeNumbers(1, 2);
	for (size_t i = 3; i < primes.size(); i += 2)
		if (primes[i])
			primeNumbers.push_back(i);
	
	QueryPerformanceCounter(&stopTime);

	// report
	if (primes.size() <= 100)
		for (auto p : primes)
			cout << p << " ";
	cout << "\n\n";

	cout << "Found: " << primeNumbers.size() << " prime numbers.\n";
	cout << fixed << setprecision(7);
	size_t constexpr TITLE_WIDTH = 10;
	size_t constexpr NUM_WIDTH = 12;
	cout << setw(TITLE_WIDTH) << "Load: " << setw(NUM_WIDTH) << elapsed_time(startLoad, stopLoad, timerFrequency) << " seconds\n";
	cout << setw(TITLE_WIDTH) << "Sieve: " << setw(NUM_WIDTH) << elapsed_time(startSieve, stopSieve, timerFrequency) << " seconds\n";
	cout << setw(TITLE_WIDTH) << "Cleanup: " << setw(NUM_WIDTH) << elapsed_time(startCleanup, stopCleanup, timerFrequency) << " seconds\n";
	cout << setw(TITLE_WIDTH) << "Total: " << setw(NUM_WIDTH) << elapsed_time(startTime, stopTime, timerFrequency) << " seconds\n";
}