#include <dirent.h>
#include <ostream>
#include <iostream>
#include "AudioLoader.h"

AudioLoader::AudioLoader(Player &player): player(player) {}

void AudioLoader::loadFromDirectory(std::string directory) {
	DIR *handle;
	handle = opendir(directory.c_str());
	if(handle == NULL) {
		throw "mhm";
	}

	struct dirent *item;
	char absolute[PATH_MAX];
	char relative[PATH_MAX];
	char code[NAME_MAX];
	while(item = readdir(handle)) {
		strcpy(relative, directory.c_str());
		strcat(relative, "/");
		strcat(relative, item->d_name);
		realpath(relative, absolute);

		if(item->d_type != DT_REG) {
			std::cout << "<6>" << "Skipping '" << absolute << "'\n";
			continue;
		}

		char *end = strstr(item->d_name, ".wav");

		if(!end) {
			std::cout << "<6>" << "Could not add '" << absolute << "'\n";
			continue;
		}

		size_t length = end - item->d_name;
		strncpy(code, item->d_name, length);
		code[length] = '\0';

		player.add(code, absolute);
	}

	closedir(handle);
}
