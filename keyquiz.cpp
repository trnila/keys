#include <ostream>
#include <iostream>
#include <sstream>
#include "Player.h"
#include "AudioLoader.h"
#include "Input/Termios.h"
#include "Modes/ListenMode.h"

int main(int argc, char* argv[]) {
	try {
		Player player;

		AudioLoader loader(player);
		try {
			loader.loadFromDirectory("voices/");
		} catch(std::runtime_error &e) {
			std::cerr << "<3>" << e.what() << "\n";
		}

		player.play();

		ListenMode mode(player);
		Termios input;

		input.addListener(&mode);

		mode.start();
		input.listen();
	} catch (std::exception &e) {
		std::cerr << "<0>" << e.what() << std::endl;
	}
}