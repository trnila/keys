#include <iostream>
#include "ListenMode.h"

ListenMode::ListenMode(Player &player): player(player) {}


void ListenMode::start() {
	nextLetter();
}

void ListenMode::onKeyPress(std::string code) {
	if(code == " ") {
		player.addToPlaylist(currentLetter);
	} else {
		if (code == currentLetter) {
			std::cout << "\x1b[32;1m\u2713";
		} else {
			std::cout << "\x1b[31;1m\u2717";
			tries++;

			if(tries >= 3) {
				std::cout << " " << currentLetter;
			} else {
				player.addToPlaylist(currentLetter);
			}
		}

		std::cout << "\x1b[0m";

		if(tries >= 3 || code == currentLetter) {
			nextLetter();
			std::cout << "\n";
		}
	}
}

std::string ListenMode::generateLetter() {
	std::string result;
	result += rand() % ('z' - 'a') + 'a';
	return result;
}

void ListenMode::nextLetter() {
	currentLetter = generateLetter();
	player.addToPlaylist(currentLetter);
	tries = 0;
}
