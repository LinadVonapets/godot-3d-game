#include "user_interface.hpp"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/animation_player.hpp>

using namespace godot;

void UserInterface::_ready()
{
	this->retry_button = get_node<Button>("Retry/RetryButton");
	this->retry = get_node<ColorRect>("Retry");
	this->total_score_label = get_node<Label>("Retry/TotalScoreLabel");
	this->score_label = get_node<Label>("ScoreLabel");

	retry->hide();
}

void UserInterface::_on_retry_button_pressed()
{
	emit_signal("on_retry_pressed");
	retry->hide();
	this->score_label->show();
}

void UserInterface::increment_score() 
{
	this->score++;
	this->score_label->set_text(String("Score: {0}").format(Array::make(this->score)));
}

void UserInterface::show_game_over_screen() 
{
	this->retry->show();
	get_node<AnimationPlayer>("Retry/RetryShadowing")->play("opacity_change");
	this->score_label->hide();
	this->total_score_label->set_text(String("Total Score: {0}").format(Array::make(this->score)));
}

void UserInterface::_bind_methods() 
{
	ClassDB::bind_method(D_METHOD("increment_score"), 
						&UserInterface::increment_score);

	ClassDB::bind_method(D_METHOD("show_game_over_screen"), 
						&UserInterface::show_game_over_screen);

	ADD_SIGNAL(MethodInfo("on_retry_pressed"));
	
	ClassDB::bind_method(D_METHOD("_on_retry_button_pressed"), 
						&UserInterface::_on_retry_button_pressed);
}
