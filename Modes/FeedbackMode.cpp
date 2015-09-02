#include "FeedbackMode.h"

FeedbackMode::FeedbackMode(Player &player): player(player) {}

void FeedbackMode::onKeyPress(std::string code) {
	player.addToPlaylist(code);
}

void FeedbackMode::start() {}
