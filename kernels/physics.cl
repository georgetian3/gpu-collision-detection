R"(

inline bool outside(double v) {
    return v < 0.0 || v > 1.0;
}


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
    double3 new_velocity = collidable.velocity + gravity * dt;
    double3 new_position = collidable.position + (collidable.velocity + new_velocity) * (0.5 * dt);
    new_position.x = clamp(new_position.x, -100.0, 100.0);
    new_position.y = clamp(new_position.y, -100.0, 100.0);
    new_position.z = clamp(new_position.z, -100.0, 100.0);

    collidables[i].position = new_position;
    collidables[i].velocity = new_velocity;
    // if (outside(new_position.x) || outside(new_position.y) || outside(new_position.z)) {
    //     collidables[i].immovable = 1;
    // }
}

)"