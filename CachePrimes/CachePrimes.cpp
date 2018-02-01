#include <iostream>
#include <iomanip>
#include <locale>
#include <vector>
using namespace std;
#include <Windows.h>

using prime_type = unsigned long long;
prime_type constexpr MAX_TEST = 100'000;

bool is_prime(prime_type n, vector<prime_type> const& primes) {
	prime_type limit = (prime_type)sqrt(n);
	for (auto p : primes) {
		if (p > limit)
			return true;
		if (n % p == 0)
			return false;
	}
	return true;
}

int main() {
	cout.imbue(locale(""));
	cout << "Cached Primes" << endl;
	cout << "Search [2.." << MAX_TEST << "] for prime numbers.\n";

	LARGE_INTEGER timerFreq;
	QueryPerformanceFrequency(&timerFreq);
	cout << "Freq = " << timerFreq.QuadPart << endl;

	LARGE_INTEGER startTime, stopTime;
	// find primes 
	QueryPerformanceCounter(&startTime);
	vector<prime_type> primes;
	for (prime_type i = 2; i < MAX_TEST; ++i)
		if (is_prime(i, primes))
			primes.push_back(i);
	QueryPerformanceCounter(&stopTime);

	// report
	if (primes.size() <= 100)
		for (auto p : primes)
			cout << p << ' ';
	cout << endl;
	cout << "Found: " << primes.size() << " prime numbers.\n";
	double elapsedTime = double(stopTime.QuadPart - startTime.QuadPart) / timerFreq.QuadPart;
	cout << "Elapsed time = " << setprecision(16) << fixed << elapsedTime << endl;
}