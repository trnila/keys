#include "Input.h"

void Input::addListener(KeyPressListener *listener) {
	listeners.push_back(listener);
}

void Input::notifyAll(std::string code) {
	for(KeyPressListener* listener: listeners) {
		listener->onKeyPress(code);
	}
}
