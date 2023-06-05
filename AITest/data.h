#pragma once

#include <vector>
#include <string>

class Data
{
public:
	std::string name;
	float score;
	float number;
	float avgScore;
	Data(std::string);
};

Data::Data(std::string title)
{
	name = title;
	number = 0;
	score = 0;
	avgScore = 0;
}
