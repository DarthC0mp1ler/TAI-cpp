#pragma once
#include "Perceptron.h"
#include <fstream>
#include <iostream>
#include <filesystem>
#include <map>
#include <vector>
#include <string>

#define TRAINING_FILE_PATH "D:\\PJATK\\NAI\\NAI_03\\LanguagesTrain"
#define TEST_FILE_PATH "D:\\PJATK\\NAI\\NAI_03\\LanguagesTest"

#define __NOT_CLASSIFIED "NOT CLASSIFIED"

namespace fs = std::filesystem;

using namespace std;
class Algorithm
{
	map<string, vector<map<char, double>>> trainingData, testData;
	vector<Perceptron> _perceptrons;
	string _text;

public :
	Algorithm(string trainingDataPath, string testDataPath);
	Algorithm(string trainingDataPath, string s, int i );
	
private:
	void readFile(string path, map<string, vector<map<char, double>>>& dataSet);
	map<char, double> readText(string path);
	map<char, double> readInput(string text);

	void relativeFrequency(map<string, vector<map<char, double>>>& m);
	void adjustWeights();
public:
	string getResult(map<char, double>);
	void calcStats(int &succ,int &nsucc);

	void adjust(map<char, double> m, int d, int o, Perceptron& p);
	string getOneRes();
	

};




