#ifndef KEY_INPUT_H
#define KEY_INPUT_H

#include <string>
#include <vector>

class KeyPressListener {
public:
	virtual void onKeyPress(std::string code) = 0;
};

class Input {
public:
	void addListener(KeyPressListener* listener);
	virtual void listen() = 0;
protected:
	void notifyAll(std::string code);
private:
	std::vector<KeyPressListener*> listeners;
};


#endif //KEY_INPUT_H
