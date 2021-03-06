// random_number.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <chrono>
#include <random>
using namespace std;

int main()

{
	default_random_engine silnik;
	uniform_real_distribution<double> rozklad(3, 10);
	auto czas = chrono::system_clock::now();
	auto ziarno = czas.time_since_epoch();
	silnik.seed(ziarno.count());

	double random = rozklad(silnik);

	cout << random<<endl;

    return 0;
}

