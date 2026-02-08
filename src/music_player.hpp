#ifndef __MUSIC_PLAYER_HPP
#define __MUSIC_PLAYER_HPP

#include <godot_cpp/classes/audio_stream_player.hpp>

namespace godot 
{

class MusicPlayer : public AudioStreamPlayer 
{
    GDCLASS(MusicPlayer, AudioStreamPlayer)
protected:
    static void _bind_methods();

public:
    void restart();
    void start_pitchdown();

private:
    void _on_pitch_down_timer_timeout();

};

} // namespace godot

#endif