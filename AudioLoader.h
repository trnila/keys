#ifndef KEY_AUDIOLOADER_H
#define KEY_AUDIOLOADER_H

#include "Player.h"

class AudioLoader {
public:
	AudioLoader(Player &player);
	void loadFromDirectory(std::string directory);
private:
	Player &player;
};

#endif //KEY_AUDIOLOADER_H
