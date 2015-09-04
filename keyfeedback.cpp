#include <ostream>
#include <iostream>
#include <sstream>
#include <boost/program_options.hpp>
#include "Player.h"
#include "AudioLoader.h"
#include "Input/RawInput.h"
#include "Modes/ListenMode.h"
#include "Modes/FeedbackMode.h"

namespace po = boost::program_options;

int main(int argc, char* argv[]) {
	std::string rawDevice;

	try {
		po::options_description desc("Allowed options");
		desc.add_options()
				("help", "produce help message")
				("device", po::value<std::string>(&rawDevice)->required(), "location of raw events device, look at /dev/input/by-id for a keyboard device")
				;

		po::variables_map vm;
		po::store(po::parse_command_line(argc, argv, desc), vm);
		po::notify(vm);

		if (vm.count("help")) {
			std::cout << desc << "\n";
			return 1;
		}
	} catch(po::error &e) {
		std::cout << e.what() << "\n";
		return 1;
	}

	try {
		Player player;

		AudioLoader loader(player);
		try {
			loader.loadFromDirectory("voices/");
		} catch(std::runtime_error &e) {
			std::cerr << "<3>" << e.what() << "\n";
		}

		player.play();

		FeedbackMode mode(player);
		RawInput input(rawDevice);
		input.addListener(&mode);

		mode.start();
		input.listen();
	} catch (std::exception &e) {
		std::cerr << "<0>" << e.what() << std::endl;
	}
}