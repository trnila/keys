#include <SDL.h>
#include <ostream>
#include <iostream>
#include "Player.h"

Uint8 *audio_pos; // global pointer to the audio buffer to be played
Uint32 audio_len; // remaining length of the sample we have to play

Player::Player() {
	if (SDL_Init(SDL_INIT_AUDIO) < 0) {
		throw "Could not initialize SDL audio";
	}

	audio_len = 0;

	SDL_AudioSpec want, have;
	SDL_zero(want);
	want.freq = 22050;
	want.format = AUDIO_S16LSB;
	want.channels = 1;
	want.samples = 4096;
	want.callback = [&](void *userdata, Uint8 *stream, int len) {
	    if (audio_len == 0) {
		    return;
	    }


	    len = ( len > audio_len ? audio_len : len );
	    SDL_memcpy (stream, audio_pos, len); 					// simply copy from one buffer into the other
	    //SDL_MixAudio(stream, audio_pos, len, SDL_MIX_MAXVOLUME);// mix from one buffer into another

	    audio_pos += len;
	    audio_len -= len;
	};

	audioDevice = SDL_OpenAudioDevice(NULL, 0, &want, &have, SDL_AUDIO_ALLOW_FORMAT_CHANGE);
}

void Player::add(char code, std::string path) {
	Letter l(path);
	letters.insert({code, l});
}

void Player::addToPlaylist(char letter) {
	queue.push(letter);
}


void Player::play() {
	SDL_PauseAudioDevice(audioDevice, 0);

	while(1) {
		if(audio_len == 0) {
			if (!queue.empty()) {
				std::cout << "a" << std::endl;
				SDL_PauseAudioDevice(audioDevice, 1);
				char letter = queue.front();
				queue.pop();

				auto it = letters.find(letter);
				if (it == letters.end()) {
					throw "Not faund";
				}
				audio_pos = it->second.buffer;
				audio_len = it->second.length;

				SDL_PauseAudioDevice(audioDevice, 0);
			}
		}
		SDL_Delay(1000);
	}
}
