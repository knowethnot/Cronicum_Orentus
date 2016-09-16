#include <SDL2/SDL.h>
#include <iostream>

namespace
{
	const char* file_path = { "./audio/test.wav" };
}

struct AudioDatum
{
	Uint8* pos;
	Uint32 length;
};

void AudioCallback(void* userData, Uint8* stream, int streamLength)
{
	AudioDatum* audio = (AudioDatum*)userData;

	if (audio->length == 0) return;

	Uint32 length = (Uint32)streamLength;
	length = (length > audio->length ? audio->length : length);

	SDL_memcpy(stream, audio->pos, length);

	audio->pos += length;
	audio->length -= length;
}


int Demonium()
{
	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_AudioSpec wavSpec;
	Uint8* wavStart;
	Uint32 wavLength;


	if (SDL_LoadWAV(file_path, &wavSpec, &wavStart, &wavLength) == NULL)
	{
		// TODO: Proper Error Handliing
		std::cerr << "\nERROR: " << file_path << std::endl;
		return 1;
	}

	AudioDatum audio;
	audio.pos = wavStart;
	audio.length = wavLength;

	wavSpec.callback = AudioCallback;
	wavSpec.userdata = &audio;

	SDL_AudioDeviceID device = SDL_OpenAudioDevice(NULL, 0, &wavSpec, NULL, SDL_AUDIO_ALLOW_ANY_CHANGE);

	if (device == 0) std::cerr << "\nERROR: " << SDL_GetError() << std::endl;

	SDL_PauseAudioDevice(device, 0);	// 0 - to play 1 - to pause

	while (audio.length > 0)
	{
		SDL_Delay(100);
	}

	SDL_CloseAudioDevice(device);
	SDL_FreeWAV(wavStart);
	SDL_Quit();

	return EXIT_SUCCESS;
}

int main()
{
	Demonium();

	std::cout << "\nPress [ENTER] To Quit ...." << std::endl;
	std::cin.ignore(10, '\n');
	std::cin.get();

	return 0;
}
