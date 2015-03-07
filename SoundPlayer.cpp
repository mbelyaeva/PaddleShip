#include "SoundPlayer.h"

SoundPlayer::SoundPlayer()
{
	SDL_Init(SDL_INIT_AUDIO);
	Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);

	//bgMusic = Mix_LoadMUS("sounds/bgMusic.wav");
	//Mix_PlayMusic(bgMusic, -1);

	Mix_AllocateChannels(24);

	paddleSwing = Mix_LoadWAV("sounds/paddleSwing.mp3");
	score = Mix_LoadWAV("sounds/score.mp3");
	shipHit = Mix_LoadWAV("sounds/shipHit.mp3");
}

void SoundPlayer::startBgMusic()
{
}

void SoundPlayer::playPaddleSwing()
{
	if (Mix_Playing(1) == 0)
		Mix_PlayChannel(1, paddleSwing, 0);
}
void SoundPlayer::playScore()
{
	if (Mix_Playing(2) == 0)
		Mix_PlayChannel(2, score, 0);
}
void SoundPlayer::playShipHit()
{
	if (Mix_Playing(3) == 0)
		Mix_PlayChannel(3, shipHit, 0);
}