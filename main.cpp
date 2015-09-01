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
		loader.loadFromDirectory("voices/");

		player.play();

		RawInput input(std::string("/dev/input/event4"));
		input.listen(player);
	} catch (const char *e) {
		std::cout << e << std::endl;
	}
}