#include "Perceptron.h"

using namespace std;

Perceptron::Perceptron(string name, int r): _name(name),_length(123-96)
{
	int length = 122 - 96;
	for (size_t i = 0; i < length+1; i++)
	{
		_vec.push_back(random*r);
	}
}


string Perceptron::getName()
{
	return _name;
}

double Perceptron::getWeight(size_t index)
{
	if (index >= _vec.size()) return -1;
	return _vec.at(index);
}

void Perceptron::updateWeight(size_t index, double inputValue, int desiredOutput, int actualOutput)
{
	_vec.at(index) =  _vec.at(index) + double(desiredOutput - actualOutput) * inputValue;
}

int Perceptron::getOutput(map<char, double> m)
{
	double res = 0;
	size_t i = 0;
	for (const auto& m1 : m)
	{
		res += _vec.at(i) * m1.second;
		i++;
	}
	res -= _vec.at(i);
	if (res >= 0) return 1;
	else return 0;
}

size_t Perceptron::getLength()
{
	return _length;
}
