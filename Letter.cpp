#include <SDL_audio.h>
#include <SDL_timer.h>
#include <iostream>
#include "Letter.h"

SDL_AudioSpec a;
Letter::Letter(std::string path) {
	if(SDL_LoadWAV(path.c_str(), &a, &buffer, &length) == NULL) {

		throw path.c_str();
	}
}

void Letter::play() {
	std::cout << "playing" << std::endl;


	SDL_PauseAudio(0);

	SDL_Delay(3000);

}
