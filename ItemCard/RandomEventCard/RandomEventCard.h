//
// Created by Kai Huang on 2025/5/4.
//

#ifndef RANDOMEVENTCARD_H
#define RANDOMEVENTCARD_H
#include "../Base/ItemCard.h"
#include <cstdlib>
#include <ctime>
#include "nlohmann/json.hpp"
#include <fstream>
#include <string>
#include <sstream>


class RandomEventCard : public ItemCard {
public:
	nlohmann::json eventData;
	ifstream event;

	RandomEventCard() {
		name = "Random Event";
		description = "Trigger Random Events.";
		price = 10000;

		event.open("json/event.json");

		if (event.fail()) {
			cout << "Falied to open event.json\n";
			return 0;
		}

		event >> eventData;
		event.close();
	}
	static bool use(Player& player) {
		// TODO 隨機事件

		srand(time(NULL));

		int randNum = rand() % MaxEvent;

		cout << "Event " << randNum << '\n';
		cout << eventData[to_string(randNum)]["text"].get<string>() << '\n';
		string function = eventData[to_string(randNum)]["function"].get<string>();

		stringstream ssfun(function);
		while (ssfun >> function) {
			if (function == "sub") {
				int delta;
				ssfun >> delta;
				processPlayer[turn]->subMoney(delta);
			}
			else if (function == "add") {
				int delta;
				ssfun >> delta;
				processPlayer[turn]->addMoney(delta);
			}
			else if (function == "level") {
				int newLevel;
				ssfun >> newLevel;
				string area;

				int i = 0;
				for (auto x : countryData) {
					landNameToPos[x["name"].get<string>()] = i;
					i++;
				}

				while (ssfun >> area) {
					if (area != "end") {
						processMap[landNameToPos[area]].setLevel(0);
					}
					else {
						break;
					}
				}
			}
			else if (function == "hospital") {
				int day;
				ssfun >> day;
				processPlayer[turn]->setStayInHospitalTurn(day);
				processPlayer[turn]->setPos(min(abs(32 - processPlayer[turn]->getPos()), abs(63 - processPlayer[turn]->getPos())));
			}
			else if (function == "fly") {
				string area;

				int i = 0;
				for (auto x : countryData) {
					landNameToPos[x["name"].get<string>()] = i;
					i++;
				}

				ssfun >> area;
				processPlayer[turn]->.setPos(landNameToPos[area]);
			}
			else if (function == "run") {
				runMinigame();
			}
		}

		return true;
	}
};

#endif //RANDOMEVENTCARD_H
