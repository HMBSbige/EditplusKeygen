#include "Timer.h"
RandomNum::RandomNum(){};
int RandomNum::getNum(int a, int b) {
	if (a > b)
		swap(a, b);
	mt19937 gen(rd());
	uniform_int_distribution<> dis(a, b);
	return dis(gen);
}
Timer::Timer() {};
void Timer::start() { 
	s = clock(); 
}
void Timer::finish() {
	f = clock(); 
}
double Timer::totaltime() { 
	return (double)(f - s) / CLOCKS_PER_SEC; 
}