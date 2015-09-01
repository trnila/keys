#ifndef KEY_RAWINPUT_H
#define KEY_RAWINPUT_H

#include <string>
#include <sys/epoll.h>
#include "Player.h"

class RawInput {
public:
	RawInput(std::string devicePath);
	void listen(Player &player);
private:
	int fd, efd;
	struct epoll_event ee;
};


#endif //KEY_RAWINPUT_H
