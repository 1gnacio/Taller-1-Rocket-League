//
// Created by igb on 05/12/22.
//

#include "sdl_music.h"

sdl_music::sdl_music(): background_music(DATA_PATH "/sounds/background.ogg"),
                        goal_chunk(DATA_PATH "/sounds/goal.mp3"),
                        accelerating_chunk(DATA_PATH "/sounds/acceleration.mp3"),
                        turbo_chunk(DATA_PATH "/sounds/turbo.mp3"),
                        jump_chunk(DATA_PATH "/sounds/jump.mp3"),
                        kick_chunk(DATA_PATH "/sounds/kick.mp3"),
                        goal(false), playing_goal(false),turbo(false),
                        playing_turbo(false), accelerating(false), playing_accelerating(false),
                        jumping(false), playing_jump(false), kick(false), playing_kick(false)
                        {}

void sdl_music::update(bool _goal, bool _turbo, bool _accelerating, bool _jumping, bool _kick) {
    this->goal= _goal;
    this->turbo = _turbo;
    this->accelerating = _accelerating;
    this->jumping = _jumping;
    this->kick = _kick;
}

void sdl_music::renderSounds(SDL2pp::Mixer& mixer) {
    if (turbo && !playing_turbo){
        mixer.PlayChannel(TURBO_CH, turbo_chunk);
        playing_turbo = true;
    } else if (!turbo && playing_turbo) {
        playing_turbo = false;
        mixer.FadeOutChannel(TURBO_CH,0);
    }
    if (goal && !playing_goal){
        mixer.PlayChannel(GOAL_CH, goal_chunk);
        playing_goal = true;
    } else if (!goal && playing_goal) {
        playing_goal = false;
        mixer.FadeOutChannel(GOAL_CH,0);
    }
    if (accelerating && !playing_accelerating){
        mixer.PlayChannel(ACCEL_CH, accelerating_chunk);
        playing_accelerating = true;
    } else if (!accelerating && playing_accelerating) {
        playing_accelerating = false;
        mixer.FadeOutChannel(ACCEL_CH,0);
    }
    if (jumping && !playing_jump){
        mixer.PlayChannel(JUMP_CH, jump_chunk);
        playing_jump = true;
    } else if (!jumping && playing_jump) {
        playing_jump = false;
        mixer.FadeOutChannel(ACCEL_CH,0);
    }
    if (kick && !playing_kick){
        mixer.PlayChannel(KICK_CH, kick_chunk);
        playing_kick = true;
    } else if (!kick && playing_kick) {
        playing_kick = false;
        mixer.FadeOutChannel(KICK_CH,0);
    }
}

void sdl_music::startBackgroundMusic(SDL2pp::Mixer& mixer) {
    mixer.FadeInMusic(background_music);
}
