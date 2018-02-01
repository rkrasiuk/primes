#include <iostream>
#include <iomanip>
#include <locale>
#include <vector>
using namespace std;
#include <Windows.h>

using prime_type = unsigned long long;
prime_type constexpr MAX_TEST = 10'000'000;

bool is_prime(prime_type n) {
	//auto highestPossibleFactor = n / 2;
	auto highestPossibleFactor = sqrt(n);
	for (prime_type divisor = 2; divisor < highestPossibleFactor; ++divisor)
		if (n % divisor == 0)
			return false;
	return true;
}

int main() {
	cout.imbue(locale(""));
	cout << "Search [2.." << MAX_TEST << "] for prime numbers.\n";

	LARGE_INTEGER timerFreq;
	QueryPerformanceFrequency(&timerFreq);
	cout << "Freq = " << timerFreq.QuadPart << endl;

	LARGE_INTEGER startTime, stopTime;
	// find primes 
	QueryPerformanceCounter(&startTime);
	vector<prime_type> primes{ 2 };
	for (prime_type i = 3; i < MAX_TEST; i+=2)
		if (is_prime(i))
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