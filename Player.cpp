#include <SDL.h>
#include <ostream>
#include <iostream>
#include "Player.h"

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
	want.userdata = (void*) this;
	want.callback = Player::audioCallbackProxy;

	audioDevice = SDL_OpenAudioDevice(NULL, 0, &want, &have, SDL_AUDIO_ALLOW_FORMAT_CHANGE);
}

void Player::add(std::string code, std::string path) {
	std::cout << "<5>" << "Adding '" << code << "' from ;" << path << "'\n";
	letters.insert({code, Letter(code, path)});
}

Letter* Player::getLetter(std::string code) {
	auto it = letters.find(code);
	if(it == letters.end()) {
		return NULL;
	}

	return &it->second;
}

void Player::addToPlaylist(std::string code) {
	std::cout << "<5>Adding  " << code << " to queue\n";

	Letter *letter = getLetter(code);
	if(letter) {
		queue.push(letter);
	} else {
		std::cout << "<4>Could not play '" << code << "'\n";
	}
}

void Player::play() {
	SDL_PauseAudioDevice(audioDevice, 0);
}

void Player::audioCallbackProxy(void *userdata, Uint8 *stream, int len) {
	((Player*)userdata)->audioCallback(stream, len);
}

void Player::audioCallback(Uint8 *stream, int len) {
	if (audio_len == 0) {
		if(!queue.empty()) {
			Letter *letter = queue.front();
			audio_pos = letter->buffer;
			audio_len = letter->length;

			std::cout << "<6>Playing " << letter->getCode() << "\n";

			queue.pop();
		} else {
			return;
		}
	}

	len = ( len > audio_len ? audio_len : len );
	SDL_memcpy (stream, audio_pos, len); 					// simply copy from one buffer into the other
	//SDL_MixAudio(stream, audio_pos, len, SDL_MIX_MAXVOLUME);// mix from one buffer into another

	audio_pos += len;
	audio_len -= len;
}
