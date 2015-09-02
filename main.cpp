#include <ostream>
#include <iostream>
#include <sstream>
#include <boost/program_options.hpp>
#include "Player.h"
#include "AudioLoader.h"
#include "Input/RawInput.h"
#include "Input/Termios.h"
#include "Modes/ListenMode.h"
#include "Modes/FeedbackMode.h"

namespace po = boost::program_options;

enum class ModeType {
	Feedback,
	Listen,
};

std::istream& operator>>(std::istream& in, ModeType& type) {
	std::string token;
	in >> token;
	if(token == "feedback") {
		type = ModeType::Feedback;
	} else if(token == "listen") {
		type = ModeType::Listen;
	} else {
		throw boost::program_options::invalid_option_value(token);
	}

	return in;
}

enum class InputType {
	Raw,
	Termios
};

std::istream& operator>>(std::istream& in, InputType& type) {
	std::string token;
	in >> token;
	if(token == "raw") {
		type = InputType::Raw;
	} else if(token == "termios") {
		type = InputType::Termios;
	} else {
		throw boost::program_options::invalid_option_value(token);
	}

	return in;
}

int main(int argc, char* argv[]) {
	ModeType modeType = ModeType::Listen;
	InputType inputType = InputType::Termios;
	std::string rawDevice;


	try {
		po::options_description desc("Allowed options");
		desc.add_options()
				("help", "produce help message")
				("mode", po::value<ModeType>(&modeType), "mode could be one of listen, feedback")
				("input", po::value<InputType>(&inputType), "input could be one of termios, raw")
				("device", po::value<std::string>(&rawDevice), "location of raw events device")
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

		Mode *mode;
		if(modeType == ModeType::Listen) {
			mode = new ListenMode(player);
		} else if(modeType == ModeType::Feedback) {
			mode = new FeedbackMode(player);
		}

		Input *input;
		if(inputType == InputType::Termios) {
			input = new Termios();
		} else if(inputType == InputType::Raw) {
			input = new RawInput(rawDevice);
		}
		input->addListener(mode);

		mode->start();
		input->listen();

		//RawInput input(std::string("/dev/input/event4"));
		//input.listen(player);
	} catch (std::exception &e) {
		std::cerr << "<0>" << e.what() << std::endl;
	}
}