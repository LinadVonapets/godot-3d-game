#include "score_label.hpp"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/array.hpp>

using namespace godot;

void ScoreLabel::_bind_methods() 
{
	ClassDB::bind_method(D_METHOD("_on_mob_squashed"), &ScoreLabel::_on_mob_squashed);
}

void ScoreLabel::_on_mob_squashed() 
{
	this->score++;
	set_text(String("Score: {0}").format(Array::make(this->score)));
}