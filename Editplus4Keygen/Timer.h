#pragma once
#include <iostream>
#include <ctime>
#include <random>
using namespace std;
class RandomNum {
private:
	random_device rd;
public:
	RandomNum();
	int getNum(int a, int b);
};
class Timer {
private:
	clock_t s, f;
public:
	Timer();
	void start();
	void finish();
	double totaltime();
};