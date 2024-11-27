#include <SDL2/SDL.h>
#include <string>
using namespace std;

void init(){
    SDL_Init(SDL_INIT_AUDIO);
}

void close(){
     SDL_Quit();
}

void playSound(string fileName)
{

    SDL_AudioSpec wav_spec;
    Uint32 wav_length;
    Uint8 *wav_buffer;
    const char * file = fileName.c_str();

    if (SDL_LoadWAV(file, &wav_spec, &wav_buffer, &wav_length))
    {
        SDL_AudioDeviceID deviceId = SDL_OpenAudioDevice(NULL, 0,  &wav_spec, NULL, 0);

        if (deviceId)
        {
            int success = SDL_QueueAudio(deviceId, wav_buffer, wav_length);

            SDL_PauseAudioDevice(deviceId, 0);
            
            SDL_CloseAudioDevice(deviceId);
        
        }
        else
        SDL_ShowSimpleMessageBox(0, "Error", "Audio driver failed to initialize", NULL);

        SDL_FreeWAV(wav_buffer);
    }
    else
        SDL_ShowSimpleMessageBox(0, "Error", "wav failed to load", NULL);

}
