#include <stdlib.h>
#include <fcntl.h>
#include <linux/input.h>
#include <string.h>
#include <errno.h>
#include <sys/epoll.h>
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <ostream>
#include <iostream>
#include <sstream>
#include "Player.h"


#define MAX_EVENTS 1000
#define MUS_PATH "voices/0.wav"

// prototype for our audio callback
// see the implementation for more information
void my_audio_callback(void *userdata, Uint8 *stream, int len);

char *keys[] = {"RESERVED", "ESC", "1", "2", "3", "4", "5", "6", "7", "8", "9", "0", "-", "=", "BACKSPACE", "TAB", "q", "w", "e", "r", "t", "y", "u", "i", "o", "p", "", "", "ENTER", "LEFT_CTRL", "a", "s", "d", "f", "g", "h", "j", "k", "l", ";", "KEY_APOSTROPHE", "KEY_GRAVE", "LEFT_SHIFT", "\\", "z", "x", "c", "v", "b", "n", "m", ",", ".", "/", "RIGHT_SHIFT", "*", "LEFT_ALT", "SPACE", "CAPS_LOCK", "F1", "F2", "F3", "F4", "F5", "F6", "F7", "F8", "F9", "F10", "NUMLOCK", "SCROLLLOCK", "KP7", "KP8", "KP9", "KPMINUS", "KP4", "KP5", "KP6", "KPPLUS", "KP1", "KP2", "KP3", "KP0", "KPDOT", "F11", "F12", "KPENTER", "RIGHT_CTRL", "KPSLASH", "SYSRQ", "RIGHTALT", "LINEFEED", "HOME", "UP", "PAGEUP", "LEFT", "RIGHT", "END", "DOWN", "PAGEDOWN", "INSERT", "DELETE", "KPEQUAL", "KPPLUSMINUS", "PAUSE",};

// variable declarations
static Uint8 *audio_pos; // global pointer to the audio buffer to be played
static Uint32 audio_len; // remaining length of the sample we have to play

int main(int argc, char* argv[]){
	try {
		Player player;
		for(int i = 0; i < 10; i++) {
			std::ostringstream os;
			os << "voices/" << i << ".wav";

			player.add(i, os.str());
		}

		pthread_t thread1;
		pthread_create(&thread1, NULL, [&](void* arg) -> void* {
			try {
				((Player *) arg)->play();
			} catch(char const* e) {
				std::cout << e << std::endl;
			}
		}, (void*) &player);

		SDL_Delay(1000);

		player.addToPlaylist(0);

		//for(int i = 0; i < 10; i++) {
		//	player.addToPlaylist(i);
		///	SDL_Delay(600);
		//}


	//	pthread_join(thread1, NULL);
	//	return 0;




		struct epoll_event ee;
		struct input_event ev;

		int fd = open("/dev/input/event4", O_RDONLY | O_NOCTTY );
		int efd = epoll_create(sizeof(fd));
		ee.events = EPOLLIN;
		int cfg = epoll_ctl(efd, EPOLL_CTL_ADD, fd, &ee);

		while(1) {
			int ret = epoll_wait(efd, &ee, MAX_EVENTS, -1);
			read(fd, &ev, sizeof(ev));

			//std::cout << ev.value << std::endl;
			if(ev.value == 1) {
				printf("%s\n", keys[ev.code]);

				if(keys[ev.code][0] >= '0' && keys[ev.code][0] <= '9') {
					player.addToPlaylist(keys[ev.code][0] - '0');
					//char buffer[100];
					//snprintf(buffer, 99, "aplay voices/%s.wav", keys[ev.code]);
					//system(buffer);
				}
			}
		}

		pthread_join(thread1, NULL);

	} catch (const char* e) {
		std::cout << e << std::endl;
	}


	return 0;
	// Initialize SDL.
	if (SDL_Init(SDL_INIT_AUDIO) < 0)
			return 1;

	// local variables
	static Uint32 wav_length; // length of our sample
	static Uint8 *wav_buffer; // buffer containing our audio file
	static SDL_AudioSpec wav_spec; // the specs of our piece of music


	/* Load the WAV */
	// the specs, length and buffer of our wav are filled
	if( SDL_LoadWAV(MUS_PATH, &wav_spec, &wav_buffer, &wav_length) == NULL ){
	  return 1;
	}
	// set the callback function
	wav_spec.callback = my_audio_callback;
	wav_spec.userdata = NULL;
	// set our global static variables
	audio_pos = wav_buffer; // copy sound buffer
	audio_len = wav_length; // copy file length

	/* Open the audio device */
	if ( SDL_OpenAudio(&wav_spec, NULL) < 0 ){
	  fprintf(stderr, "Couldn't open audio: %s\n", SDL_GetError());
	  exit(-1);
	}



struct epoll_event ee;
	struct input_event ev;

	int fd = open("/dev/input/event4", O_RDONLY | O_NOCTTY );
	int efd = epoll_create(sizeof(fd));
	ee.events = EPOLLIN;
	int cfg = epoll_ctl(efd, EPOLL_CTL_ADD, fd, &ee);

	while(1) {
		int ret = epoll_wait(efd, &ee, MAX_EVENTS, -1);
		read(fd, &ev, sizeof(ev));

		if(ev.value == 1) {
			printf("%s\n", keys[ev.code]);

			if(keys[ev.code][0] >= 'a' && keys[ev.code][0] <= 'z') {
				//char buffer[100];
				//snprintf(buffer, 99, "aplay voices/%s.wav", keys[ev.code]);
				//system(buffer);
			}
		}
	}




	/* Start playing */
	SDL_PauseAudio(0);

	// wait until we're don't playing
	while ( audio_len > 0 ) {
		SDL_Delay(100);
	}

	// shut everything down
	SDL_CloseAudio();
	SDL_FreeWAV(wav_buffer);

}
/*
// audio callback function
// here you have to copy the data of your audio buffer into the
// requesting audio buffer (stream)
// you should only copy as much as the requested length (len)
void my_audio_callback(void *userdata, Uint8 *stream, int len) {

	if (audio_len ==0)
		return;

	len = ( len > audio_len ? audio_len : len );
	SDL_memcpy (stream, audio_pos, len); 					// simply copy from one buffer into the other
	//SDL_MixAudio(stream, audio_pos, len, SDL_MIX_MAXVOLUME);// mix from one buffer into another

	audio_pos += len;
	audio_len -= len;
}
*/