/* Exercise the same TiMidity decoder shipped in Switch SDL2_mixer 2.0.4. */
#include "SDL.h"
#include "timidity.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    if (argc < 2) return 2;
    SDL_setenv("TIMIDITY_CFG", argv[1], 1);
    int initialized = Timidity_Init();
    if (argc == 2) {
        /* The old package had neither config nor usable GUS instruments. */
        if (initialized == 0) Timidity_Exit();
        return initialized == -1 ? 0 : 3;
    }
    if (initialized != 0) { fprintf(stderr, "config: %s\n", SDL_GetError()); return 4; }
    SDL_AudioSpec spec;
    SDL_zero(spec);
    spec.freq = 44100;
    spec.format = AUDIO_S16SYS;
    spec.channels = 2;
    spec.samples = 2048;
    for (int i = 2; i < argc; ++i) {
        SDL_RWops *rw = SDL_RWFromFile(argv[i], "rb");
        MidiSong *song = Timidity_LoadSong(rw, &spec);
        if (!song) { fprintf(stderr, "%s: %s\n", argv[i], SDL_GetError()); return 5; }
        Timidity_Start(song);
        Sint16 pcm[4096];
        int peak = 0;
        int frames = 0;
        /* Decode up to 20 seconds, including intros with delayed notes. */
        while (frames < 44100 * 20) {
            int bytes = Timidity_PlaySome(song, pcm, sizeof(pcm));
            if (bytes <= 0) break;
            for (int j = 0; j < bytes / (int)sizeof(pcm[0]); ++j) {
                int value = abs((int)pcm[j]);
                if (value > peak) peak = value;
            }
            frames += bytes / 4;
        }
        printf("%s: frames=%d peak=%d duration_ms=%u\n", argv[i], frames, peak,
               Timidity_GetSongLength(song));
        Timidity_FreeSong(song);
        SDL_RWclose(rw);
        if (!frames || !peak) return 6;
    }
    Timidity_Exit();
    return 0;
}
