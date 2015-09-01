#include <SDL_audio.h>
#include <SDL_timer.h>
#include <iostream>
#include "Letter.h"

Letter::Letter(std::string code, std::string path): code(code) {
	SDL_AudioSpec a;
	if(SDL_LoadWAV(path.c_str(), &a, &buffer, &length) == NULL) {
		throw path.c_str();
	}
}

const std::string Letter::getCode() {
	return code;
}

void Letter::play() {
	std::cout << "playing" << std::endl;

	SDL_PauseAudio(0);

	SDL_Delay(3000);

}
