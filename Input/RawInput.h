#ifndef KEY_RAWINPUT_H
#define KEY_RAWINPUT_H

#include <string>
#include <sys/epoll.h>
#include "../Player.h"
#include "Input.h"

class RawInput: public Input {
public:
	RawInput(std::string devicePath);
	void listen();
private:
	int fd, efd;
	struct epoll_event ee;
};


#endif //KEY_RAWINPUT_H
