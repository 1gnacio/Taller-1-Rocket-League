//
// Created by igb on 05/12/22.
//

#ifndef ROCKET_LEAGUE_SDL_MUSIC_H
#define ROCKET_LEAGUE_SDL_MUSIC_H

#define AUDIO_CHANNELS 6

#include <SDL2pp/SDL2pp.hh>
#include <SDL2pp/SDLMixer.hh>

enum {TURBO_CH, GOAL_CH, ACCEL_CH, JUMP_CH, KICK_CH};
class sdl_music {
private:
    SDL2pp::Music background_music;
    SDL2pp::Chunk goal_chunk;
    SDL2pp::Chunk accelerating_chunk;
    SDL2pp::Chunk turbo_chunk;
    SDL2pp::Chunk jump_chunk;
    SDL2pp::Chunk kick_chunk;
    bool goal;
    bool playing_goal;
    bool turbo;
    bool playing_turbo;
    bool accelerating;
    bool playing_accelerating;
    bool jumping;
    bool playing_jump;
    bool kick;
    bool playing_kick;
public:
    sdl_music();
    void update(bool goal, bool turbo, bool accelerating, bool jumping, bool kick);
    void renderSounds(SDL2pp::Mixer& mixer);
    void startBackgroundMusic(SDL2pp::Mixer& mixer);
    ~sdl_music() = default;
};


#endif //ROCKET_LEAGUE_SDL_MUSIC_H
