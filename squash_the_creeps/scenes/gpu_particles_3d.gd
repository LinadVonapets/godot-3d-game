extends GPUParticles3D

func set_particle_color(color) -> void:
	((self.draw_pass_1 as PlaneMesh).material as StandardMaterial3D).albedo_color = color

# Called when the node enters the scene tree for the first time.
func _ready() -> void:
	set_particle_color(Color(0.177, 0.681, 0.68, 1.0))


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta: float) -> void:
	set_particle_color(get_parent().get_floor_color())
