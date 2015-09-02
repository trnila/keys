#ifndef KEY_MODE_H
#define KEY_MODE_H

class Mode: public KeyPressListener {
public:
	virtual void start() = 0;
};

#endif //KEY_MODE_H
