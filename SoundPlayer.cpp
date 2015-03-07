#include <iostream>
#include "SoundPlayer.h"

SoundPlayer::SoundPlayer()
{
	int sdlret = SDL_Init(SDL_INIT_AUDIO);
        if(sdlret == -1){
                std::cout << "SDL value: " << sdlret << std::endl;
                std::cout << SDL_GetError();
        }
	Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);

	/*bgMusic = Mix_LoadMUS("sounds/bgMusic.wav");
	if(bgMusic == NULL) {
		std::cout << Mix_GetError() << std::endl;
	}*/
	//Mix_PlayMusic(bgMusic, -1);

	Mix_AllocateChannels(24);

	paddleSwing = Mix_LoadWAV("sounds/paddleSwing.wav");
	score = Mix_LoadWAV("sounds/score.wav");
	shipHit = Mix_LoadWAV("sounds/shipHit.wav");

	mute = false;
}

void SoundPlayer::startBgMusic()
{	
	/*if (Mix_PlayingMusic() == 0) {
		int err = Mix_PlayMusic(bgMusic, -1);
		if (err == -1){
            std::cout << SDL_GetError() << std::endl;
		}
	} else if (Mix_PausedMusic() == 1) {
		Mix_ResumeMusic();
	} else {
		Mix_PauseMusic();
	}*/
}

void SoundPlayer::playPaddleSwing()
{
	if (Mix_Playing(1) == 0 && !mute){
		Mix_PlayChannel(1, paddleSwing, 0);
	}
}
void SoundPlayer::playScore()
{
	if (Mix_Playing(2) == 0 && !mute)
		Mix_PlayChannel(2, score, 0);
}
void SoundPlayer::playShipHit()
{
	if (Mix_Playing(3) == 0 && !mute)
		Mix_PlayChannel(3, shipHit, 0);
}

void SoundPlayer::soundOn(){
	mute = false;
}
void SoundPlayer::soundOff(){
	mute = true;
}