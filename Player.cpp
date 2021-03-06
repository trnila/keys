#include <SDL.h>
#include <ostream>
#include <iostream>
#include <sstream>
#include "Player.h"

Player::Player() {
	if (SDL_Init(SDL_INIT_AUDIO) < 0) {
		std::ostringstream os;
		os << "Could not initialize SDL audio: " << SDL_GetError();
		throw std::runtime_error(os.str());
	}

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

Player::~Player() {
	SDL_CloseAudioDevice(audioDevice);
}

void Player::add(std::string code, std::string path) {
	try {
		letters.insert({code, Audio(code, path)});
		std::cerr << "<5>" << "Adding '" << code << "' from '" << path << "'\n";
	} catch(std::runtime_error &e) {
		std::cerr << "<3>" << e.what() << "\n";
	}
}

Audio* Player::getLetter(std::string code) {
	auto it = letters.find(code);
	if(it == letters.end()) {
		return NULL;
	}

	return &it->second;
}

void Player::addToPlaylist(std::string code) {
	std::cerr << "<5>Adding  " << code << " to queue\n";

	mutex.lock();

	Audio *letter = getLetter(code);
	if(letter) {
		queue.push(letter);
	} else {
		std::cerr << "<4>Could not play '" << code << "'\n";
	}

	mutex.unlock();
}

void Player::play() {
	SDL_PauseAudioDevice(audioDevice, 0);
}

void Player::audioCallbackProxy(void *userdata, Uint8 *stream, int len) {
	((Player*)userdata)->audioCallback(stream, len);
}

void Player::audioCallback(Uint8 *stream, size_t len) {
	if(track.isFinished()) {
		mutex.lock();
		if(!queue.empty()) {
			Audio *audio = queue.front();
			queue.pop();
			track.setAudio(audio);

			std::cerr << "<5>Playing '" << audio->getCode() << "'\n";
		}
		mutex.unlock();
	}

	if(!track.isFinished()) {
		track.playNextSamples(stream, len);
	}
}
