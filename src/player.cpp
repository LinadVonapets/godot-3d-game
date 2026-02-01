#include "player.hpp"

using namespace godot;

void Player::_bind_methods() {
    ClassDB::bind_method(D_METHOD("get_speed"), &Player::get_speed);
    ClassDB::bind_method(D_METHOD("set_speed", "speed"), &Player::set_speed);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "Speed"), "set_speed", "get_speed");

    ClassDB::bind_method(D_METHOD("get_fall_acceleration"), &Player::get_fall_acceleration);
    ClassDB::bind_method(D_METHOD("set_fall_acceleration", "fall_acceleration"), &Player::set_fall_acceleration);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "Fall Acceleration"), "set_fall_acceleration", "get_fall_acceleration");
    
    ClassDB::bind_method(D_METHOD("get_jump_impulse"), &Player::get_jump_impulse);
    ClassDB::bind_method(D_METHOD("set_jump_impulse", "jump_impulse"), &Player::set_jump_impulse);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "Jump Impulse"), "set_jump_impulse", "get_jump_impulse");
}

void Player::set_speed(const int speed) { 
    this->speed = speed; 
}

int Player::get_speed() const { 
    return this->speed; 
}  

void Player::set_fall_acceleration(const int fall_acceleration) { 
    this->fall_acceleration = fall_acceleration; 
}

int Player::get_fall_acceleration() const {
    return this->fall_acceleration;
}

void Player::set_jump_impulse(const int jump_impulse) { 
    this->jump_impulse = jump_impulse; 
}

int Player::get_jump_impulse() const { 
    return this->jump_impulse; 
}

Player::Player() {
    m_input = Input::get_singleton();
}

void Player::_physics_process(double delta) {
    Vector3 direction;

    if (m_input->is_action_pressed("move_right"))
        direction.x += 1;
    if (m_input->is_action_pressed("move_left"))
        direction.x -= 1;
    if (m_input->is_action_pressed("move_forward"))
        direction.z -= 1;
    if (m_input->is_action_pressed("move_back"))
        direction.z += 1;

    if (!direction.is_zero_approx()) {
        direction.normalize();
        get_node<Node3D>("Pivot")->set_basis(Basis::looking_at(direction));
    }

    target_velocity.x = direction.x * speed;
    target_velocity.z = direction.z * speed;

    // if (is_on_floor() && m_input->is_action_just_pressed("jump")) {
    //     target_velocity.y = jump_impulse;
    // }

    if(!is_on_floor()) {
        target_velocity.y -= fall_acceleration * (float)delta;
        
    }
    if (m_input->is_action_just_pressed("jump"))
            target_velocity.y = jump_impulse;

    set_velocity(target_velocity);
    move_and_slide();
}