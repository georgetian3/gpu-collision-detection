R"(

__kernel void update_physics(__global struct Collidable* collidables, const double dt, const struct vec3 gravity) {
    const int i = get_global_id(0);
    struct Collidable collidable = collidables[i];
    struct vec3 new_velocity = vec_add(collidable.velocity, vec_mul(gravity, dt));
    collidable.position = vec_mul(vec_add(collidable.velocity, new_velocity), 0.5 * dt);
    collidable.velocity = new_velocity;
    collidables[i] = collidable;
}



)"