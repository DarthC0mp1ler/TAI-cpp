#include "algorithm.h"

#include <iostream>

std::vector<Algorithm::Attribute> Algorithm::maxVal(std::vector<Attribute> a, std::vector<Attribute> b) {

	int sum1 = 0, sum2 = 0;
	for (auto a : a)
	{
		sum1 += a.value;
	}
	for (auto b : b)
	{
		sum2 += b.value;
	}
	return (sum1 > sum2) ? a : b;
}

std::vector<Algorithm::Attribute> Algorithm::knapSack(int W, std::vector<Attribute> v, int n)
{
	if (n == 0 || W == 0) {
		return std::vector<Attribute>();
	}
	if (v.at(n - 1).size > W) {
		return knapSack(W, v, n - 1);
	}
	else {
		std::vector<Attribute> vec1 = knapSack(W - v.at(n - 1).size, v, n - 1);
		vec1.push_back(v.at(n - 1));
		std::vector<Attribute> vec2 = knapSack(W, v, n - 1);
		return maxVal(vec1, vec2);
	}
}

Algorithm::Algorithm(std::string filePath) : filePath(filePath)
{
	dataSets = ReadInformation();
	
	printDataSet();
}

Algorithm::~Algorithm() {}


std::vector<Algorithm::DataSet> Algorithm::ReadInformation()
{
	
	//std::cout << "reading" << std::endl;
	std::ifstream file;
	file.open(filePath);

	std::string word;
	for (size_t i = 0; i < 5; i++)
	{
		file >> word;
		if (i == 2) length = std::stoi(word.substr(0, word.size() - 1));
		if (i == 4) capacity = std::stoi(word);
		std::cout << word << std::endl;
	}

	//std::cout << "Length " << length << std::endl;
	//std::cout << "capacity " << capacity << std::endl;

	std::vector<DataSet> vector;
	while (file >> word)
	{
		//std::cout << word << std::endl;
		if (word == "dataset")
		{
			//std::cout << "NEW DATASET //////////////////////////";
			file >> word;
			int number = std::stoi(word.substr(0, word.size() - 1));
			//std::cout << number << std::endl;
			std::vector<Attribute> vect;
			

			std::string vals;
			std::getline(file,word);
			std::getline(file, word);
			std::getline(file, vals);

			word = word.substr(word.find_first_of('{') + 1, word.find_first_of('}') - 1);
			vals = vals.substr(vals.find_first_of('{') + 1, vals.find_first_of('}') - 1);
			std::cout << word << std::endl;
			std::cout << vals << std::endl;

			for (size_t i = 1; i < length+1; i++)
			{
				Attribute att;
				att.setSize(std::stoi(word.substr(0, word.find_first_of(','))));
				word = word.substr(word.find_first_of(',')+1);
				att.setValue(std::stoi(vals.substr(0, vals.find_first_of(','))));
				vals= vals.substr(vals.find_first_of(',') + 1);
				att.setNumber(i);
				vect.push_back(att);
			}
			DataSet  ds{number,vect};
			vector.push_back(ds);
		}
		
	}
	std::cout << vector.size() << std::endl;
	return vector;
}


void Algorithm::printDataSet()
{
	std::cout << "Datasets " << dataSets.size() << std::endl;
	for (auto ds : dataSets)
	{
		std::cout << "Dataset " << ds.number << std::endl<<"{ ";
		for (auto attr : ds.attributes)
		{
			std::cout << attr.number << ", ";
		}
		std::cout << " }" << std::endl << "{ ";
		for (auto attr : ds.attributes)
		{
			std::cout << attr.size << ", ";
		}
		std::cout << " }" << std::endl << "{ ";
		for (auto attr : ds.attributes)
		{
			std::cout << attr.value << ", ";
		}
		std::cout << " }" << std::endl;
	}
}


void Algorithm::getKnapsack(int num, std::vector<Attribute> &vec)
{
	std::cout << num << std::endl;

	std::vector<Attribute> vect;
	for (auto v : dataSets)
	{
		if (v.number == num) vect = v.attributes;
	}

	std::vector<Attribute> res = knapSack(capacity,vect,length);

	std::cout << "knapsack " << res.size() <<std::endl;
	int i = 0, b = 0;
	for (auto attr : res)
	{
		std::cout << attr.number << " : " << attr.size << " : " << attr.value << std:: endl;
		i += attr.value;
		b += attr.size;
	}
	std::cout << "val " << i << std::endl;
	std::cout << "sz " << b << std::endl;


	vec = res;
}

