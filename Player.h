#ifndef KEY_PLAYER_H
#define KEY_PLAYER_H

#include <string>
#include <unordered_map>
#include <queue>
#include <SDL_audio.h>
#include "Letter.h"

class Player {
public:
	Player();
	void add(std::string code, std::string path);
	void addToPlaylist(std::string letter);
	void play();

	static void audioCallbackProxy(void *userdata, Uint8 *stream, int len);
private:
	SDL_AudioDeviceID audioDevice;
	std::unordered_map<std::string, Letter> letters;
	std::queue<Letter*> queue;

	Uint8 *audio_pos; // global pointer to the audio buffer to be played
	Uint32 audio_len; // remaining length of the sample we have to play

	Letter * getLetter(std::string code);
	void audioCallback(Uint8 *stream, int len);
};


#endif //KEY_PLAYER_H
