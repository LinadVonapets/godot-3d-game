#ifndef __MOD_HPP
#define __MOD_HPP

#include <godot_cpp/classes/character_body3d.hpp>
#include <godot_cpp/variant/vector3.hpp>

namespace godot 
{

class Mob : public CharacterBody3D 
{
    GDCLASS(Mob, CharacterBody3D)
protected:
    static void _bind_methods();

public:
    int min_speed = 10;
    int max_speed = 18;

public:
    int get_min_speed() const;
    void set_min_speed(const int min_speed);

    int get_max_speed() const;
    void set_max_speed(const int max_speed);

    void _physics_process(double delta) override;

public:
    void initialize(Vector3 start_position, Vector3 player_position);
    void squash();

private:
    void _on_visible_on_screen_enabler_3d_screen_exited();
};

} // namespace godot

#endif