#pragma once
#include <SDL_mixer.h>
#include <vector>

class SDLmixer
{
	std::vector<Mix_Chunk *> chunks;
	std::vector<Mix_Music *> musics;
	int current_music_id = -1;
public:
	SDLmixer(int frequency, Uint16 format, int channels, int chunksize);
	~SDLmixer();

	int load_chunk(const char * audio_file);
	int load_music(const char * audio_file);
	bool play_music(int id, int loops = -1);
	bool play_chunk(int id, int loops = 0);
	int current_music();
};

