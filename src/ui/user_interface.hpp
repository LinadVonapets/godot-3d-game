#ifndef __USER_INTERFACE_HPP
#define __USER_INTERFACE_HPP

#include <godot_cpp/classes/control.hpp>
#include <godot_cpp/classes/label.hpp>
#include <godot_cpp/classes/button.hpp>
#include <godot_cpp/classes/color_rect.hpp>

namespace godot 
{

class UserInterface: public Control
{
	GDCLASS(UserInterface, Control);
protected:
	static void _bind_methods();

private:
	int score = 0;

	

public:
	void _ready() override;
	void _on_retry_button_pressed();

	void increment_score();
	void show_game_over_screen();

private:
	Label* score_label;
	Label* total_score_label;
	Button* retry_button;
	ColorRect* retry;
};

} // namespace godot

#endif