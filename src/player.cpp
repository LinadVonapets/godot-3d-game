#include "player.hpp"

#include "mob.hpp"
#include <godot_cpp/classes/animation_player.hpp>
#include <godot_cpp/classes/area3d.hpp>
#include <godot_cpp/classes/gpu_particles3d.hpp>
#include <godot_cpp/classes/static_body3d.hpp>
#include <godot_cpp/classes/mesh_instance3d.hpp>
#include <godot_cpp/classes/box_mesh.hpp>
#include <godot_cpp/classes/standard_material3d.hpp>

using namespace godot;

void Player::set_speed(const int speed) 
{ 
    this->speed = speed; 
}

int Player::get_speed() const 
{ 
    return this->speed; 
}  

void Player::set_fall_acceleration(const int fall_acceleration) 
{ 
    this->fall_acceleration = fall_acceleration; 
}

int Player::get_fall_acceleration() const 
{
    return this->fall_acceleration;
}

void Player::set_jump_impulse(const int jump_impulse) 
{ 
    this->jump_impulse = jump_impulse; 
}

int Player::get_jump_impulse() const 
{ 
    return this->jump_impulse; 
}

void Player::set_bounce_impulse(const int bounce_impulse) 
{ 
    this->bounce_impulse = bounce_impulse; 
}

int Player::get_bounce_impulse() const 
{ 
    return this->bounce_impulse; 
}

Color Player::get_floor_color() const 
{
    return this->color_of_floor;
}

void Player::_physics_process(double delta) 
{
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
        get_node<AnimationPlayer>("AnimationPlayer")->set_speed_scale(4);
        get_node<GPUParticles3D>("GPUParticles3D")->set_emitting(true);
    }
    else
    {
        get_node<AnimationPlayer>("AnimationPlayer")->set_speed_scale(1);
        get_node<GPUParticles3D>("GPUParticles3D")->set_emitting(false);
    }

    target_velocity.x = direction.x * speed;
    target_velocity.z = direction.z * speed;

    if(!is_on_floor()) {
        target_velocity.y -= fall_acceleration * (float)delta;
        get_node<GPUParticles3D>("GPUParticles3D")->set_emitting(false);
    }

    if (m_input->is_action_just_pressed("jump") && is_on_floor())
            target_velocity.y = jump_impulse;
    
    for(int index = 0; index < get_slide_collision_count(); index++) {
        Ref<KinematicCollision3D> collision = get_slide_collision(index);

        Node* collision_node = Object::cast_to<Node>(collision->get_collider());

        if (collision_node->is_in_group("ground")) {
            auto ground_static_body = Object::cast_to<StaticBody3D>(collision_node);
            auto mesh_inst = ground_static_body->get_node<MeshInstance3D>("MeshInstance3D");
            auto mesh = Object::cast_to<BoxMesh>(mesh_inst->get_mesh().ptr());
            auto material = Object::cast_to<StandardMaterial3D>(mesh->get_material().ptr());
            this->color_of_floor = material->get_albedo();
        }

        if (collision_node->is_in_group("mob")) {

            // Vector up
            if (Vector3(0, 1, 0).dot(collision->get_normal()) > 0.1) {
                Object::cast_to<Mob>(collision_node)->squash();
                target_velocity.y = bounce_impulse;
                break;
            }
        }

    }

    set_velocity(target_velocity);
    move_and_slide();

    auto pivot = get_node<Node3D>("Pivot");
    auto new_pivot_rot = Vector3(
        Math_PI/6.0f * get_velocity().y / jump_impulse,
        pivot->get_rotation().y,
        pivot->get_rotation().z
    );
    pivot->set_rotation(new_pivot_rot);
}

void Player::_unhandled_input(const Ref<InputEvent>& p_event) 
{
    if(p_event->is_action_pressed("immortal_player")) {
        d_immortal = !d_immortal;
        UtilityFunctions::print(
            String("Player immortality toggled: {0}").format(
                Array::make(this->d_immortal)
            )
        );
    }
}

Player::Player() 
{
    m_input = Input::get_singleton();
}

void Player::die() 
{
    emit_signal("hit");
    queue_free();
}

void Player::_on_mob_detector_body_entered(Node3D* body) 
{
    if (!this->d_immortal)
       die();   
}

void Player::_bind_methods() 
{
    ClassDB::bind_method(D_METHOD("get_speed"), &Player::get_speed);
    ClassDB::bind_method(D_METHOD("set_speed", "speed"), &Player::set_speed);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "Speed"), "set_speed", "get_speed");

    ClassDB::bind_method(D_METHOD("get_fall_acceleration"), &Player::get_fall_acceleration);
    ClassDB::bind_method(D_METHOD("set_fall_acceleration", "fall_acceleration"), &Player::set_fall_acceleration);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "Fall Acceleration"), "set_fall_acceleration", "get_fall_acceleration");
    
    ClassDB::bind_method(D_METHOD("get_jump_impulse"), &Player::get_jump_impulse);
    ClassDB::bind_method(D_METHOD("set_jump_impulse", "jump_impulse"), &Player::set_jump_impulse);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "Jump Impulse"), "set_jump_impulse", "get_jump_impulse");
    
    ClassDB::bind_method(D_METHOD("get_bounce_impulse"), &Player::get_bounce_impulse);
    ClassDB::bind_method(D_METHOD("set_bounce_impulse", "bounce_impulse"), &Player::set_bounce_impulse);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "Bounce Impulse"), "set_bounce_impulse", "get_bounce_impulse");

    ClassDB::bind_method(D_METHOD("_on_mob_detector_body_entered", "body"), &Player::_on_mob_detector_body_entered);

    ClassDB::bind_method(D_METHOD("get_floor_color"), &Player::get_floor_color);

    ADD_SIGNAL(MethodInfo("hit"));

}
