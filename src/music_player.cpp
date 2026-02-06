#include "music_player.hpp"

#include <godot_cpp/core/class_db.hpp>

#include <godot_cpp/classes/timer.hpp>

using namespace godot;

void MusicPlayer::_bind_methods() {
    ClassDB::bind_method(D_METHOD("_on_pitch_down_timer_timeout"), &MusicPlayer::_on_pitch_down_timer_timeout);
}

void MusicPlayer::restart() {
    this->set_pitch_scale(1.0);
    this->play();
    get_node<Timer>("PitchDownTimer")->stop();
}

void MusicPlayer::start_pitchdown() {
    get_node<Timer>("PitchDownTimer")->start();
}

void MusicPlayer::_on_pitch_down_timer_timeout(){
    
    double scale = this->get_pitch_scale() - 0.02;
    this->set_pitch_scale(scale);
    
    if (scale <= 0.01) {
        get_node<Timer>("PitchDownTimer")->stop();
        this->stop();
        this->set_pitch_scale(1.0);
    }
}