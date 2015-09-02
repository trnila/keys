#ifndef KEY_FEEDBACKMODE_H
#define KEY_FEEDBACKMODE_H

#include "../Input/Input.h"
#include "../Player.h"
#include "Mode.h"

class FeedbackMode: public Mode {
public:
	FeedbackMode(Player &player);
	virtual void start();

private:
	Player &player;
public:
	virtual void onKeyPress(std::string code);
};

#endif //KEY_FEEDBACKMODE_H
