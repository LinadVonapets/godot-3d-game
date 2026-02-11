#include "register_types.h"

#include "mob.hpp"
#include "player.hpp"
#include "main.hpp"
#include "score_label.hpp"
#include "death_sound.hpp"
#include "music_player.hpp"
#include <gdextension_interface.h>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/godot.hpp>

using namespace godot;

void init_module(ModuleInitializationLevel p_level) 
{
    if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE)
        return;
    
    GDREGISTER_RUNTIME_CLASS(MusicPlayer);
    GDREGISTER_RUNTIME_CLASS(DeathSound);
    GDREGISTER_RUNTIME_CLASS(ScoreLabel);
    GDREGISTER_RUNTIME_CLASS(Mob);
    GDREGISTER_RUNTIME_CLASS(Player);
    GDREGISTER_RUNTIME_CLASS(Main);
}

void uninit_module(ModuleInitializationLevel p_level) 
{
    if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) 
        return;
}

extern "C" 
{

GDExtensionBool GDE_EXPORT _game_logic_init(GDExtensionInterfaceGetProcAddress p_get_proc_address, const GDExtensionClassLibraryPtr p_library, GDExtensionInitialization *r_initialization) {
    godot::GDExtensionBinding::InitObject init_obj(p_get_proc_address, p_library, r_initialization);
    
    init_obj.register_initializer(init_module);   
    init_obj.register_terminator(uninit_module);
    init_obj.set_minimum_library_initialization_level(MODULE_INITIALIZATION_LEVEL_SCENE);

    return init_obj.init();
}

}