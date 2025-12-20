#include "mob.hpp"

#include <godot_cpp/core/math.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

using uf = UtilityFunctions;

void Mob::_bind_methods() {
    ClassDB::bind_method(D_METHOD("get_min_speed"), &Mob::get_min_speed);
    ClassDB::bind_method(D_METHOD("set_min_speed", "min_speed"), &Mob::set_min_speed);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "Min Speed"), "set_min_speed", "get_min_speed");

    ClassDB::bind_method(D_METHOD("get_max_speed"), &Mob::get_max_speed);
    ClassDB::bind_method(D_METHOD("set_max_speed", "max_speed"), &Mob::set_max_speed);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "Max Speed"), "set_max_speed", "get_max_speed");

    ClassDB::bind_method(D_METHOD("_on_visible_on_screen_enabler_3d_screen_exited"), &Mob::_on_visible_on_screen_enabler_3d_screen_exited);
}

void Mob::_physics_process(double delta) {
    move_and_slide();
}

void Mob::initialize(Vector3 start_position, Vector3 player_position) {

    player_position.y = 0;
    look_at_from_position(start_position, player_position);

    rotate_y(uf::randf_range(-Math_PI / 4.0, Math_PI / 4.0));

    int random_speed = uf::randi_range(min_speed, max_speed);
    
    Vector3 vel = Vector3(0, 0, -1) * random_speed;

    set_velocity(
        vel.rotated(
            Vector3(0, 1, 0), 
            get_rotation().y
        )
    );
}

void Mob::_on_visible_on_screen_enabler_3d_screen_exited() {
    queue_free();
}