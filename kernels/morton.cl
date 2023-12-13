R"(

// Expands a 10-bit integer into 30 bits
// by inserting 2 zeros after each bit.
unsigned int expandBits(unsigned int v) {
    v = (v * 0x00010001u) & 0xFF0000FFu;
    v = (v * 0x00000101u) & 0x0F00F00Fu;
    v = (v * 0x00000011u) & 0xC30C30C3u;
    v = (v * 0x00000005u) & 0x49249249u;
    return v;
}

unsigned int morton3D(float x, float y, float z) {
    unsigned int xx = expandBits((unsigned int)x);
    unsigned int yy = expandBits((unsigned int)y);
    unsigned int zz = expandBits((unsigned int)z);
    return xx * 4 + yy * 2 + zz;
}

struct Collidable {
    double x;
    double y;
    double z;
};


__kernel void mortonCodes(__global const struct Collidable* collidables, __global unsigned int* mortonCodes) {
    const int i = get_global_id(0);
    const struct Collidable collidable = collidables[i];
    printf("%d %f %f %f\n", i, collidable.x, collidable.y, collidable.z);
    mortonCodes[i] = morton3D(collidable.x, collidable.y, collidable.z);
}

)"