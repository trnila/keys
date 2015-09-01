#include <fcntl.h>
#include <linux/input.h>
#include <unistd.h>
#include <ostream>
#include <iostream>
#include <sstream>
#include "RawInput.h"

char const *keys[] = {"RESERVED", "ESC", "1", "2", "3", "4", "5", "6", "7", "8", "9", "0", "-", "=", "BACKSPACE", "TAB", "q", "w", "e", "r", "t", "y", "u", "i", "o", "p", "", "", "ENTER", "LEFT_CTRL", "a", "s", "d", "f", "g", "h", "j", "k", "l", ";", "KEY_APOSTROPHE", "KEY_GRAVE", "LEFT_SHIFT", "\\", "z", "x", "c", "v", "b", "n", "m", ",", ".", "/", "RIGHT_SHIFT", "*", "LEFT_ALT", "SPACE", "CAPS_LOCK", "F1", "F2", "F3", "F4", "F5", "F6", "F7", "F8", "F9", "F10", "NUMLOCK", "SCROLLLOCK", "KP7", "KP8", "KP9", "KPMINUS", "KP4", "KP5", "KP6", "KPPLUS", "KP1", "KP2", "KP3", "KP0", "KPDOT", "F11", "F12", "KPENTER", "RIGHT_CTRL", "KPSLASH", "SYSRQ", "RIGHTALT", "LINEFEED", "HOME", "UP", "PAGEUP", "LEFT", "RIGHT", "END", "DOWN", "PAGEDOWN", "INSERT", "DELETE", "KPEQUAL", "KPPLUSMINUS", "PAUSE",};

RawInput::RawInput(std::string devicePath) {
	fd = open(devicePath.c_str(), O_RDONLY | O_NOCTTY);
	if(!fd) {
		std::ostringstream os;
		os << "Could not open device '" << devicePath << "': " << strerror(errno);
		throw std::runtime_error(os.str());
	}

	efd = epoll_create(sizeof(fd));
	ee.events = EPOLLIN;
	int cfg = epoll_ctl(efd, EPOLL_CTL_ADD, fd, &ee);
}

void RawInput::listen(Player &player) {
	struct input_event ev;

	for(;;) {
		int ret = epoll_wait(efd, &ee, 1000, -1);
		read(fd, &ev, sizeof(ev));

		if (ev.value == 1) {
			player.addToPlaylist(keys[ev.code]);
		}
	}
}
