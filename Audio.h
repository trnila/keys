#ifndef KEY_LETTER_H
#define KEY_LETTER_H

#include <string>
#include <SDL_stdinc.h>

class Audio {
public:
	Audio(std::string code, std::string path);
	const std::string getCode();
	Uint32 getLength();

	void play(Uint8 *stream, size_t offset, size_t len);

	Uint32 length; // length of our sample
	Uint8 *buffer; // buffer cont
private:
	std::string code;
};


#endif //KEY_LETTER_H
