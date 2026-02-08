#ifndef __SCORE_LABEL_HPP
#define __SCORE_LABEL_HPP

#include <godot_cpp/classes/label.hpp>

namespace godot 
{

class ScoreLabel : public Label 
{
    GDCLASS(ScoreLabel, Label)
protected:
    static void _bind_methods();

private:
	int score = 0;
	void _on_mob_squashed();
};

} // namespace godot

#endif