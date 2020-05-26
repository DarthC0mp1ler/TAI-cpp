#include "Algorithm.h"

Algorithm::Algorithm(string trainingDataPath, string s, int i)
{
	readFile(trainingDataPath, trainingData);
	_text = s;

	relativeFrequency(trainingData);
	for (const auto& langName : trainingData)
	{
		Perceptron p(langName.first,1);
		_perceptrons.push_back(p);
	}
	adjustWeights();

	readInput(_text);
	relativeFrequency(testData);

}


Algorithm::Algorithm(string trainingDataPath, string testDataPath)
{
	readFile(trainingDataPath,trainingData);
	readFile(testDataPath,testData);
	relativeFrequency(trainingData);
	relativeFrequency(testData);
	for (const auto& langName : trainingData)
	{
		Perceptron p(langName.first, 1);
		_perceptrons.push_back(p);
	}
	adjustWeights();

}

void Algorithm::readFile(string path, map<string, vector<map<char, double>>> &dataSet)
{
	if (fs::exists(path))
	{
		for (const auto& dir : fs::directory_iterator(path))
		{
			vector<map<char,double>> tmp;
			for (const auto& innerDir : fs::directory_iterator(dir.path()))
			{
				if (innerDir.is_regular_file())
				{
					tmp.push_back(readText(innerDir.path().u8string()));
				}
			}
			dataSet[dir.path().filename().u8string()] = tmp;
		}
	}
	else 
	{
		cerr << "DIRECTORY DOES NOT EXIST" << endl;
		exit(-1);
	}
}

map<char,double> Algorithm::readText(string path)
{
	map<char, double> res;
	int i = 97;
	while (i >= 97 && i <= 122) 
	{
		res[i] = 0;
		i++;
	}
	ifstream in(path);
	char ch;
	in.get(ch);
	while (!in.fail())
	{
		ch = tolower(ch);
		if(ch >= 97 && ch <=122)
		{
			res[ch]++;
		}
		in.get(ch);
	}
	in.close();
	return res;
}

map<char, double> Algorithm::readInput(string text)
{
	map<string, vector<map<char, double>>> tmp;
	map<char, double> res;
	int i = 97;
	while (i >= 97 && i <= 122)
	{
		res[i] = 0;
		i++;
	}
	i = 0;
	while (i < text.size())
	{
		char ch = text[i];
		ch = tolower(ch);
		if (ch >= 97 && ch <= 122)
		{
			res[ch]++;
		}
		i++;
	}
	
	tmp["NONE"].push_back(res);
	testData = tmp;
	return res;
}


void Algorithm::relativeFrequency(map<string, vector<map<char, double>>> &m)
{
	map<string, vector<map<char, double>>> tmp;
	for (auto& p : m)
	{
		vector<map<char, double>> v;
		for (auto& p1 : p.second) {
			int size = 0;
			for (auto& x : p1) {
				size += x.second;
			}
			map<char, double> m1;
			for (auto& x : p1) {
				
				m1[x.first] = x.second / size;
			}
			v.push_back(m1);
		}
		tmp[p.first] = v;
	}
	m = tmp;
}

void Algorithm::calcStats(int &succ, int &nsucc)
{
	
	for (auto& langName : testData)
	{
		for ( auto& text : langName.second)
		{
			if (getResult(text) == langName.first) succ++;
			else nsucc++;
		}
	}
}

string Algorithm::getOneRes() 
{
	return getResult(testData["NONE"].at(0));
}


string Algorithm::getResult(map<char,double> m)
{
	string s = "";
	for (auto& percep : _perceptrons)
	{
		int o = percep.getOutput(m);
		if (o == 1) return percep.getName();
		
	}
	return s;
}

void Algorithm::adjustWeights()
{
	for (auto& percep : _perceptrons)
	{
		bool b = true;
		while (b) {
			b = false;
			for (const auto& langName : trainingData)
			{
				int i = 0;
				for (const auto& text : langName.second)
				{
					int o = percep.getOutput(text), d;
					if (percep.getName() == langName.first) d = 1;
					else d = 0;
					while (o != d)
					{
						b = true;
						adjust(text,d,o,percep);
						o = percep.getOutput(text);

					}
				}
				
			}
		}
	}
}

void Algorithm::adjust(map<char, double> m, int d, int o, Perceptron& p)
{
	int i = 0;
	for (const auto& a : m)
	{
		p.updateWeight(i, a.second, d, o);
		i++;
	}
}
