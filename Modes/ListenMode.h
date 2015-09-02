#ifndef KEY_LISTENMODE_H
#define KEY_LISTENMODE_H

#include "../Input/Input.h"
#include "../Player.h"
#include "Mode.h"

class ListenMode: public Mode {
public:
	ListenMode(Player &player);
	virtual void onKeyPress(std::string code);
	virtual void start();

private:
	Player &player;
	std::string currentLetter;
	int tries;

	std::string generateLetter();
	void nextLetter();
};


#endif //KEY_LISTENMODE_H
