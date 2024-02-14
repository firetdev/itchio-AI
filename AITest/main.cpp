#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cstdlib>
#include <regex>
#include "dataSet.h"
#include "data.h"
#include "game.h"

int main() {
	std::vector<std::string> tagNames = {"FPS", "Horror", "2D", "RPG", "Platformer"};
	DataSet* tags = new DataSet();
	std::vector<Game*> games;
	float change = 3;
	//Import old training
	std::ifstream oldDataFile("trainingFile.txt");
	std::string oldGame;
	int oldLine = 0;
	while(getline(oldDataFile, oldGame)) {
		oldLine++;
		for(int i = 0; i < tagNames.size(); i++) {
			if(std::regex_match(oldGame, std::regex("[A-Za-z0-9]+" + tagNames[i] + "[A-Za-z0-9:;]+"))) {
				int level = 0;
				std::string score;
				std::string number;
				for(int i = 0; i < oldGame.length(); i++) {
					if(oldGame[i - 1] == *":") {
						level = 1;
					}
					if(oldGame[i - 1] == *";") {
						level = 2;
					}
					if(level == 1 && oldGame[i] != *";") {
						score += oldGame[i];
					}
					if(level == 2 && oldGame[i] != *";") {
						number += oldGame[i];
					}
				}
				if(!tags->exists(tagNames[i])) {
					tags->add(new Data(tagNames[i]));
				}
				tags->getByName(tagNames[i])->score += std::stoi(score);
				tags->getByName(tagNames[i])->number += std::stoi(number);
			}
			if(std::regex_match(oldGame, std::regex("CHANGE[A-Za-z0-9:;]+"))) {
				oldGame.erase(0, 6);
				change = std::stoi(oldGame);
			}
		}
	}
	oldDataFile.close();
	//Do new training
	std::ifstream dataFile("dataFile.txt");
	std::string game;
	std::vector<std::string> gameTags;
	DataSet* gameTagsData = new DataSet();
	int line = 0;
	int totalTries = 0;
	while(getline(dataFile, game)) {
		gameTags.clear();
		gameTagsData->set.clear();
		line++;
		for(int i = 0; i < tagNames.size(); i++) {
			if(std::regex_match(game, std::regex("[A-Za-z0-9]+" + tagNames[i] + "[A-Za-z0-9]+"))) {
				gameTags.push_back(tagNames[i]);
			}
		}
		for(int i = 0; i < gameTags.size(); i++) {
			if(!tags->exists(gameTags[i])) {
				tags->add(new Data(gameTags[i]));
			}
			gameTagsData->add(tags->getByName(gameTags[i]));
			tags->getByName(gameTags[i])->score += line;
			tags->getByName(gameTags[i])->number++;
			tags->getByName(gameTags[i])->avgScore = tags->getByName(gameTags[i])->score / tags->getByName(gameTags[i])->number;
		}
		games.push_back(new Game(*gameTagsData));
		int tries = 0;
		while(games.back()->predictPosition(change, line) != 0) {
			tries++;
			totalTries++;
			change += games.back()->predictPosition(change, line);
		}
		if(games.back()->predictPosition(change, line) == 0) {
			tries++;
			totalTries++;
			std::cout << "Got " << line << " correct in " << tries <<" tries!" << std::endl;
		}
		tries = 0;
	}
	dataFile.close();
	std::ofstream saveFile("trainingFile.txt");
	for(int i = 0; i < tags->set.size(); i++) {
		saveFile << tags->set[i]->name << ":" << tags->set[i]->score << ";" << tags->set[i]->number << "\n";
	}
	saveFile << "CHANGE" << change;
	saveFile.close();
	std::cout << tags->getByName("RPG")->avgScore << std::endl;
	std::cout << "TOTAL TRIES: " << totalTries;
	return 0;
}
