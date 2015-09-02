#ifndef KEY_TERMIOS_H
#define KEY_TERMIOS_H

#include <termios.h>
#include "../Player.h"
#include "Input.h"

class Termios: public Input {
public:
	Termios();
	~Termios();
	void listen();
private:
	struct termios old_tio;
};

#endif //KEY_TERMIOS_H
