R"(

__kernel void update_physics(
    __global struct Collidable* collidables,
    const double3 gravity,
    const double dt
) {
    const int i = get_global_id(0);

    struct Collidable collidable = collidables[i];
    if (collidable.immovable) {
        return;
    }
    // kinematic equations
    double3 new_velocity = collidable.velocity + gravity * dt;
    double3 new_position = collidable.position + (collidable.velocity + new_velocity) * (0.5 * dt);

    new_position.x = clamp(new_position.x, -0.2, 1.2);
    new_position.y = clamp(new_position.y, -0.2, 1.2);
    new_position.z = clamp(new_position.z, -0.2, 1.2);

    collidables[i].position = new_position;
    collidables[i].velocity = new_velocity;

}

)"