R"(

// https://www.forceflow.be/2013/10/07/morton-encodingdecoding-through-bit-interleaving-implementations/
inline ulong expandBits3(double v) {
    ulong u = ((ulong)(v * (1ul << 63))) >> 43; 
    u = (u | u << 32) & 0x001f00000000ffff;
    u = (u | u << 16) & 0x001f0000ff0000ff;
    u = (u | u << 8 ) & 0x100f00f00f00f00f;
    u = (u | u << 4 ) & 0x10c30c30c30c30c3;
    u = (u | u << 2 ) & 0x1249249249249249;
    return u;
}

inline ulong morton3D(double x, double y, double z) {
    return (expandBits3(x) << 2) | (expandBits3(y) << 1) | expandBits3(z);
}

__kernel void mortonCodeAABB(__global struct Collidable* collidables) {
    const int i = get_global_id(0);
    const struct Collidable collidable = collidables[i];
    const double3 position = collidables[i].position;

    printf("%d %d %d (%f %f %f) %d (%f %f %f) (%f %f %f) (%f %f %f)\n",
        collidable.id, collidable.type, collidable.immovable,
        collidable.position.x, collidable.position.y, collidable.position.z,
        collidable.mortonCode,
        collidable.aabb.min.x, collidable.aabb.min.y, collidable.aabb.min.z, 
        collidable.aabb.max.x, collidable.aabb.max.y, collidable.aabb.max.z, 
        collidable.velocity.x, collidable.velocity.y, collidable.velocity.y
    );

    collidables[i].mortonCode = morton3D(position.x, position.y, position.z);
    printf("morton code %d\n", collidables[i].mortonCode);
}

)"