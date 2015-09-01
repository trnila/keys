#ifndef KEY_TRACK_H
#define KEY_TRACK_H

#include "Audio.h"

class Track {
public:
	Track();
	void setAudio(Audio *audio);
	void playNextSamples(Uint8 *stream, size_t len);
	bool isFinished();

private:
	size_t position;
	Audio *audio;
};


#endif //KEY_TRACK_H
