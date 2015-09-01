#include <ostream>
#include <iostream>
#include <sstream>
#include "Player.h"
#include "AudioLoader.h"
#include "RawInput.h"

int main(int argc, char* argv[]) {
	try {
		Player player;

		AudioLoader loader(player);
		try {
			loader.loadFromDirectory("voices/");
		} catch(std::runtime_error &e) {
			std::cout << "<3>" << e.what() << "\n";
		}

		player.play();

		RawInput input(std::string("/dev/input/event4"));
		input.listen(player);
	} catch (std::exception &e) {
		std::cout << "<0>" << e.what() << std::endl;
	}
}