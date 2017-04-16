#include "SDLmixer.h"
#include "SDLexception.h"

SDLmixer::SDLmixer(int frequency, Uint16 format, int channels, int chunksize)
{
	Mix_OpenAudio(frequency, format, channels, chunksize);
}


SDLmixer::~SDLmixer()
{
	for (Mix_Chunk * chunk : chunks)
		Mix_FreeChunk(chunk);
	for (Mix_Music * music : musics)
		Mix_FreeMusic(music);
	Mix_Quit();
}

int SDLmixer::load_chunk(const char * audio_file)
{
	Mix_Chunk * chunk = Mix_LoadWAV(audio_file);
	if (chunk == nullptr)
		throw SDLexception(Mix_GetError());
	chunks.push_back(chunk);
}

int SDLmixer::load_music(const char * audio_file)
{
	Mix_Music * music = Mix_LoadMUS(audio_file);
	if (music == nullptr)
		throw SDLexception(Mix_GetError());
	musics.push_back(music);
}

bool SDLmixer::play_music(int id, int loops)
{
	bool success = !Mix_PlayMusic(musics[id], loops);
	if (success)
		current_music_id = id;
	return success;
}

bool SDLmixer::play_chunk(int id, int loops)
{
	return !Mix_PlayChannel(-1, chunks[id], loops);
}

int SDLmixer::current_music()
{
	if (Mix_PlayingMusic())
		return current_music_id;
}
