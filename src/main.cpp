#include "main.hpp"
#include "mob.hpp"
#include "player.hpp"
#include "death_sound.hpp"
#include "music_player.hpp"

#include <godot_cpp/classes/path_follow3d.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/classes/timer.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/classes/audio_stream_player.hpp>
#include <godot_cpp/classes/color_rect.hpp>


using namespace godot;

void Main::_bind_methods() 
{
    ClassDB::bind_method(D_METHOD("get_mob_scene"), &Main::get_mob_scene);
    ClassDB::bind_method(D_METHOD("set_mob_scene", "mob_scene"), &Main::set_mob_scene);
    ADD_PROPERTY(
        PropertyInfo(
            Variant::OBJECT, 
            "Mob Scene", 
            PROPERTY_HINT_RESOURCE_TYPE, 
            "PackedScene"
        ), 
        "set_mob_scene", 
        "get_mob_scene"
    );

    ClassDB::bind_method(D_METHOD("_on_mob_timer_timeout"), &Main::_on_mob_timer_timeout);
    ClassDB::bind_method(D_METHOD("_on_player_hit"), &Main::_on_player_hit);

    ADD_SIGNAL(MethodInfo("game_over"));
    ADD_SIGNAL(MethodInfo("mob_squashed"));
    ClassDB::bind_method(D_METHOD("restart_game"), &Main::restart_game);
}

Ref<PackedScene> Main::get_mob_scene() const 
{ 
    return this->mob_scene; 
}

void Main::set_mob_scene(Ref<PackedScene> mob_scene) 
{ 
    this->mob_scene = mob_scene; 
}

void Main::_ready() 
{
    
}

void Main::_unhandled_input(const Ref<InputEvent> &p_event) 
{
    // if(p_event->is_action_pressed("ui_accept"))
    //     this->restart_game();
}

void Main::_on_mob_timer_timeout() 
{

    if (mob_scene.is_null()) {
        print_error("There is no mob_scene property set on Main scene!");
        return;
    }
        
    
    Mob* mob = Object::cast_to<Mob>(mob_scene->instantiate());

    auto mob_spawn_location = get_node<PathFollow3D>("SpawnPath/SpawnLocation");

    mob_spawn_location->set_progress_ratio(UtilityFunctions::randf());

    Vector3 player_position = get_node<Player>("Player")->get_position();

    mob->initialize(mob_spawn_location->get_position(), player_position);

    mob->connect("squashed", Callable(get_node<DeathSound>("DeathSound"), "_on_mob_squashed"));
    mob->connect("squashed", Callable(this, "emit_signal").bind("mob_squashed"));

    add_child(mob);
}

void Main::_on_player_hit() 
{
    get_node<Timer>("MobTimer")->stop();
    emit_signal("game_over");
    // get_node<ColorRect>("UserInterface/Retry")->show();
    get_node<MusicPlayer>("/root/MusicPlayer")->start_pitchdown();
}

void Main::restart_game() 
{
    get_node<MusicPlayer>("/root/MusicPlayer")->restart();
    get_tree()->reload_current_scene();
}