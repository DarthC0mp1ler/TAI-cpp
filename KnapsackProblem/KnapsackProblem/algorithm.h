#include <string>
#include <vector>
#include <fstream>

#ifndef _ALGORITHM_H_
#define _ALGORITHM_H_

class Algorithm
{
public:
	struct Attribute
	{
		size_t number;
		int size;
		int value;

		void setNumber(int num) { number = num; }
		void setSize(int sz) { size = sz; }
		void setValue(int val) { value = val; }

	};

	struct DataSet
	{
		int number;
		std::vector<Attribute> attributes;
	};

private:

	std::string filePath;
	std::vector<DataSet> dataSets;
	int capacity;
	int length;
	std::vector<Attribute> maxVal (std::vector<Attribute> a, std::vector<Attribute> b);
	std::vector<Attribute> knapSack(int W, std::vector<Attribute> v, int n);
public:

	Algorithm(std::string);
	~Algorithm();

	int getCapacity() { return capacity; }
	int getLength() { return length; }

	void getKnapsack(int,std::vector<Attribute>&);
	int getDatasetQuantity() { return dataSets.size(); }

private:
	std::vector<DataSet> ReadInformation();
	void printDataSet();

	
};

#endif

