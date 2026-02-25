#include "main_menu.hpp"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/classes/engine.hpp>

using namespace godot;

void MainMenu::_ready()
{
	this->music_player = get_node<MusicPlayer>("/root/MusicPlayer");
	music_player->stop();
}

void MainMenu::_on_new_game_button_down()
{
	get_tree()->change_scene_to_file("res://scenes/main.tscn");
	music_player->play();
}

void MainMenu::_on_exit_button_down()
{
	get_tree()->quit();
}

void MainMenu::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("_on_new_game_button_down"),
						&MainMenu::_on_new_game_button_down);
	ClassDB::bind_method(D_METHOD("_on_exit_button_down"),
						&MainMenu::_on_exit_button_down);
}
