#ifndef __MAIN_HPP
#define __MAIN_HPP

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/packed_scene.hpp>
#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/classes/input_event.hpp>

namespace godot 
{

class Main : public Node 
{
    GDCLASS(Main, Node);
protected:
    static void _bind_methods();

public:
    Ref<PackedScene> mob_scene;
    Ref<PackedScene> get_mob_scene() const;
    void set_mob_scene(Ref<PackedScene> mob_scene);

    void _ready() override;
    void _unhandled_input(const Ref<InputEvent> &p_event) override;

private:
    void _on_mob_timer_timeout();
    void _on_player_hit();
    void _on_retry_button_button_down();

    void restart_game();

};

} // namespace godot

#endif