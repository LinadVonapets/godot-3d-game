#ifndef __MAIN_MENU_HPP
#define __MAIN_MENU_HPP

#include <godot_cpp/classes/control.hpp>
#include "../music_player.hpp"


namespace godot {
class MainMenu: public Control 
{
	GDCLASS(MainMenu, Control);
private:
	MusicPlayer* music_player;

public:
	void _ready() override;

	void _on_new_game_button_down();
	void _on_exit_button_down();

protected:
	static void _bind_methods();
};
} // namespace godot

#endif