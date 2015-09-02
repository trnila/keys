#include <unistd.h>
#include <iostream>
#include "Termios.h"

Termios::Termios() {
	struct termios new_tio;
	unsigned char c;

	/* get the terminal settings for stdin */
	tcgetattr(STDIN_FILENO, &old_tio);

	/* we want to keep the old setting to restore them a the end */
	new_tio=old_tio;

	/* disable canonical mode (buffered i/o) and local echo */
	new_tio.c_lflag &=(~ICANON & ~ECHO);

	/* set the new settings immediately */
	tcsetattr(STDIN_FILENO,TCSANOW,&new_tio);
}

Termios::~Termios() {
	tcsetattr(STDIN_FILENO,TCSANOW, &old_tio);
}

void Termios::listen() {
	for(;;) {
		char c = getchar();
		std::string str;
		str += c;

		notifyAll(str);
	}
}
