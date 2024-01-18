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
    if (i == 0) {
        printf("sizeof(Collidable): %d\n", sizeof(struct Collidable));
    }
    const double3 position = collidables[i].position;
    collidables[i].mortonCode = morton3D(position.x, position.y, position.z);
}

)"