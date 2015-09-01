#include <SDL_audio.h>
#include <SDL_timer.h>
#include <iostream>
#include "Audio.h"

Audio::Audio(std::string code, std::string path): code(code) {
	SDL_AudioSpec a;
	if(SDL_LoadWAV(path.c_str(), &a, &buffer, &length) == NULL) {
		throw path.c_str();
	}
}

const std::string Audio::getCode() {
	return code;
}

Uint32 Audio::getLength() {
	return length;
}

void Audio::play(Uint8 *stream, size_t offset, size_t len) {
	len = len > length ? length : len;
	SDL_memcpy(stream, buffer + offset, len);
}
