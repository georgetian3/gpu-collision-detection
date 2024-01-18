R"(

// double clamp(double value, double min, double max) {
//     return value < min ? min : value > max ? max : value;
// }

__kernel void update_physics(
    __global struct Collidable* collidables,
    const double dt,
    const double3 gravity
) {
    const int i = get_global_id(0);

    struct Collidable collidable = collidables[i];
    if (collidable.immovable) {
        return;
    }
    double3 new_velocity = vec_add(collidable.velocity, vec_mul(gravity, dt));
    double3 new_position = vec_add(collidable.position, vec_mul(vec_add(collidable.velocity, new_velocity), 0.5 * dt));
    new_position.x = clamp(new_position.x, 0.0, 1.0);
    new_position.y = clamp(new_position.y, 0.0, 1.0);
    new_position.z = clamp(new_position.z, 0.0, 1.0);

    // printf("ov nv (%f %f %f) (%f %f %f) (%f %f %f) (%f %f %f)\n",
    //     collidable.velocity.x, collidable.velocity.y, collidable.velocity.z, 
    //     new_velocity.x, new_velocity.y, new_velocity.z,
    //     collidable.position.x, collidable.position.y, collidable.position.z, 
    //     new_position.x, new_position.y, new_position.z
    // );
    collidables[i].position = new_position;
    collidables[i].velocity = new_velocity;
}

)"