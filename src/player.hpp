#ifndef __PLAYER_HPP
#define __PLAYER_HPP

#include <godot_cpp/classes/character_body3d.hpp>
#include <godot_cpp/variant/vector3.hpp>
#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/classes/input_event.hpp>

namespace godot 
{

class Player : public CharacterBody3D 
{
    GDCLASS(Player, CharacterBody3D)
private:
    Input* m_input;


    int speed = 14;
    int fall_acceleration = 75;
    int jump_impulse = 20;
    int bounce_impulse = 16;
    Vector3 target_velocity;

    bool d_immortal = false;

public:
    void set_speed(const int speed);
    int get_speed() const;
    
    void set_fall_acceleration(const int fall_acceleration);
    int get_fall_acceleration() const;

    void set_jump_impulse(const int jump_impulse);
    int get_jump_impulse() const;

    void set_bounce_impulse(const int bounce_impulse);
    int get_bounce_impulse() const;

    void _physics_process(double delta) override;

    void _unhandled_input(const Ref<InputEvent>& p_event) override;

public:
    Player();
    void die();

private:
    void _on_mob_detector_body_entered(Node3D* body);

protected:
    static void _bind_methods();
};

}

#endif
