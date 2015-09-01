#ifndef KEY_LETTER_H
#define KEY_LETTER_H

#include <string>
#include <SDL_stdinc.h>

class Letter {
public:
	Letter(std::string code, std::string path);
	const std::string getCode();

	void play();

	Uint32 length; // length of our sample
	Uint8 *buffer; // buffer cont
private:
	std::string code;
};


#endif //KEY_LETTER_H
