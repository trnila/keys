#ifndef KEY_PLAYER_H
#define KEY_PLAYER_H

#include <string>
#include <unordered_map>
#include <queue>
#include "Letter.h"

class Player {
public:
	Player();
	void add(const char code, std::string path);
	void addToPlaylist(char letter);
	void play();
private:
	SDL_AudioDeviceID audioDevice;

	std::unordered_map<char, Letter> letters;
	std::queue<char> queue;
};


#endif //KEY_PLAYER_H
