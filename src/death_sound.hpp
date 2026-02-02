#ifndef __DEATH_SOUND_HPP
#define __DEATH_SOUND_HPP

#include <godot_cpp/classes/audio_stream_player.hpp>

namespace godot {

class DeathSound : public AudioStreamPlayer {
    GDCLASS(DeathSound, AudioStreamPlayer)
protected:
    static void _bind_methods();

private:
	void _on_mob_squashed();
};

} // namespace godot

#endif