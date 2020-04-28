#pragma once
#include <vector>
#include <string>
#include <map>
#include <random>

using namespace std;

#define random double(rand()) / (double(RAND_MAX) + 1.0)

class Perceptron
{
	vector<double> _vec;
	string _name;
	size_t _length;
public:
	Perceptron(string name, int r);
	string getName();
	double getWeight(size_t index);
	void updateWeight(size_t index, double inputValue, int desiredOutput, int actualOutput);
	int getOutput(map<char, double>);
	size_t getLength();
};

