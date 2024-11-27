#include <SDL2/SDL.h>


int main()
{
    SDL_Init(SDL_INIT_AUDIO);

    SDL_AudioSpec wav_spec;
    Uint32 wav_length;
    Uint8 *wav_buffer;

    if (SDL_LoadWAV("ultima.wav", &wav_spec, &wav_buffer, &wav_length))
    {
        SDL_AudioDeviceID deviceId = SDL_OpenAudioDevice(NULL, 0,  &wav_spec, NULL, 0);

        if (deviceId)
        {
            int success = SDL_QueueAudio(deviceId, wav_buffer, wav_length);

            SDL_PauseAudioDevice(deviceId, 0);
             SDL_ShowSimpleMessageBox(0, "A", "AudiAAAAAAAAAAAAa", NULL);
            SDL_CloseAudioDevice(deviceId);
        }
        else
        SDL_ShowSimpleMessageBox(0, "Error", "Audio driver failed to initialize", NULL);

        SDL_FreeWAV(wav_buffer);
    }
    else
        SDL_ShowSimpleMessageBox(0, "Error", "wav failed to load", NULL);

    SDL_Quit();

    return 0;
}
