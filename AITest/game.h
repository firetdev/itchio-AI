#pragma once

#include <iostream>
#include <vector>
#include <string>
#include "data.h"
#include "dataSet.h"

class Game {
public:
	DataSet tags;
	std::string name;
	int score;
	Game(DataSet inputTags);
	float predictPosition(float, int);
};

Game::Game(DataSet inputTags) {
	tags = inputTags;
	name = "";
	score = 0;
	for(int i = 0; i < inputTags.set.size(); i++) {
		score += inputTags.set[i]->avgScore;
	}
	score = score / inputTags.set.size();
}

float Game::predictPosition(float change, int ans) {
	float answer = ans + 0.000000;
	if(score < answer) {
		for(int i = 0; i < tags.set.size(); i++) {
			tags.set[i]->score += change;
			tags.set[i]->avgScore = tags.set[i]->score / tags.set[i]->number;
			score = 0;
			for(int i = 0; i < tags.set.size(); i++) {
				score += tags.set[i]->avgScore;
			}
			score = score / tags.set.size();
		}
		if(score < answer) {
			return answer - score;
		} else {
			return 0;
		}
	} else if(score > answer) {
		for(int i = 0; i < tags.set.size(); i++) {
			tags.set[i]->score -= change;
			tags.set[i]->avgScore = tags.set[i]->score / tags.set[i]->number;
			score = 0;
			for(int i = 0; i < tags.set.size(); i++) {
				score += tags.set[i]->avgScore;
			}
			score = score / tags.set.size();
		}
		if(score > answer) {
			return answer - score;
		} else {
			return 0;
		}
	} else {
		return 0;
	}
}
