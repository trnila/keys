#include <stdlib.h>
#include <fcntl.h>
#include <linux/input.h>
#include <string.h>
#include <errno.h>
#include <sys/epoll.h>
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <ostream>
#include <iostream>
#include <sstream>
#include "Player.h"
#include "AudioLoader.h"


#define MAX_EVENTS 1000

char const *keys[] = {"RESERVED", "ESC", "1", "2", "3", "4", "5", "6", "7", "8", "9", "0", "-", "=", "BACKSPACE", "TAB", "q", "w", "e", "r", "t", "y", "u", "i", "o", "p", "", "", "ENTER", "LEFT_CTRL", "a", "s", "d", "f", "g", "h", "j", "k", "l", ";", "KEY_APOSTROPHE", "KEY_GRAVE", "LEFT_SHIFT", "\\", "z", "x", "c", "v", "b", "n", "m", ",", ".", "/", "RIGHT_SHIFT", "*", "LEFT_ALT", "SPACE", "CAPS_LOCK", "F1", "F2", "F3", "F4", "F5", "F6", "F7", "F8", "F9", "F10", "NUMLOCK", "SCROLLLOCK", "KP7", "KP8", "KP9", "KPMINUS", "KP4", "KP5", "KP6", "KPPLUS", "KP1", "KP2", "KP3", "KP0", "KPDOT", "F11", "F12", "KPENTER", "RIGHT_CTRL", "KPSLASH", "SYSRQ", "RIGHTALT", "LINEFEED", "HOME", "UP", "PAGEUP", "LEFT", "RIGHT", "END", "DOWN", "PAGEDOWN", "INSERT", "DELETE", "KPEQUAL", "KPPLUSMINUS", "PAUSE",};

int main(int argc, char* argv[]) {
	try {
		Player player;

		AudioLoader loader(player);
		loader.loadFromDirectory("voices/");

		player.play();


		struct epoll_event ee;
		struct input_event ev;

		int fd = open("/dev/input/event4", O_RDONLY | O_NOCTTY);
		int efd = epoll_create(sizeof(fd));
		ee.events = EPOLLIN;
		int cfg = epoll_ctl(efd, EPOLL_CTL_ADD, fd, &ee);

		while (1) {
			int ret = epoll_wait(efd, &ee, MAX_EVENTS, -1);
			read(fd, &ev, sizeof(ev));

			if (ev.value == 1) {
				player.addToPlaylist(keys[ev.code]);
			}
		}
	} catch (const char *e) {
		std::cout << e << std::endl;
	}
}