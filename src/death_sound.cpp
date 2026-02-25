#include "death_sound.hpp"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;
using uf = UtilityFunctions;

void DeathSound::_on_mob_squashed() 
{
	set_pitch_scale(uf::randf_range(0.5f, 1.5f));
	play();
}

void DeathSound::_bind_methods() 
{
	ClassDB::bind_method(D_METHOD("_on_mob_squashed"), &DeathSound::_on_mob_squashed);
}
