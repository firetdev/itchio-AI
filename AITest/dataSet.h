#pragma once

#include <vector>
#include <string>
#include <fstream>
#include "data.h"

class DataSet
{
public:
	std::vector<Data*> set;
	bool exists(std::string);
	Data* getByName(std::string);
	void add(Data* data);
	Data* lowestScore();
	DataSet();
};

DataSet::DataSet()
{
	set = {};
}

void DataSet::add(Data* data)
{
	set.push_back(data);
}

Data* DataSet::getByName(std::string name)
{
	for(int i = 0; i < set.size(); i++)
	{
		if(set[i]->name == name){
			return set[i];
		}
	}
}

bool DataSet::exists(std::string name)
{
	for(int i = 0; i < set.size(); i++)
	{
		if(set[i]->name == name)
		{
			return true;
		}
	}
	return false;
}

Data* DataSet::lowestScore()
{
	if(set.size() > 0)
	{
		Data* lowest = set[0];
		for(int i = 0; i < set.size(); i++)
		{
			if(set[i]->score < lowest->score)
			{
				lowest = set[i];
			}
		}
		return lowest;
	}
}
