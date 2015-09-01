#include "Track.h"

Track::Track() {
	position = 0;
	audio = NULL;
}

void Track::setAudio(Audio *audio) {
	this->audio = audio;
	this->position = 0;
}

void Track::playNextSamples(Uint8 *stream, size_t len) {
	if(audio) {
		audio->play(stream, position, len);
		position += len;
	}
}

bool Track::isFinished() {
	return !audio || audio->getLength() < position;
}
