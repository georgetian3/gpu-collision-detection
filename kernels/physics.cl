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

    collidables[i].position = new_position;
    collidables[i].velocity = new_velocity;

}

)"