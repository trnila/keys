#ifndef KEY_PLAYER_H
#define KEY_PLAYER_H

#include <string>
#include <unordered_map>
#include <queue>
#include <SDL_audio.h>
#include <mutex>
#include "Audio.h"
#include "Track.h"

class Player {
public:
	Player();
	~Player();
	void add(std::string code, std::string path);
	void addToPlaylist(std::string letter);
	void play();

	static void audioCallbackProxy(void *userdata, Uint8 *stream, int len);
private:
	std::mutex mutex;

	SDL_AudioDeviceID audioDevice;
	std::unordered_map<std::string, Audio> letters;
	std::queue<Audio *> queue;
	Track track;

	Audio * getLetter(std::string code);
	void audioCallback(Uint8 *stream, size_t len);
};


#endif //KEY_PLAYER_H
