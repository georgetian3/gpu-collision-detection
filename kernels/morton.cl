R"(

// Expands a 10-bit integer into 30 bits
// by inserting 2 zeros after each bit.
unsigned int expandBits(unsigned int v) {
    printf("v %u", v);
    v = (v * 0x00010001u) & 0xFF0000FFu;
    v = (v * 0x00000101u) & 0x0F00F00Fu;
    v = (v * 0x00000011u) & 0xC30C30C3u;
    v = (v * 0x00000005u) & 0x49249249u;
    return v;
}

unsigned int morton3D(double x, double y, double z) {
    unsigned int xx = expandBits((unsigned int)x);
    unsigned int yy = expandBits((unsigned int)y);
    unsigned int zz = expandBits((unsigned int)z);
    printf("x %d y %d z %d xx %u yy %u zz %u", x, y, z, xx, yy, zz);
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
    unsigned int res = morton3D(collidable.x, collidable.y, collidable.z);
    printf("%d %f %f %f %u\n", i, collidable.x, collidable.y, collidable.z, res);
    mortonCodes[i] = res;
}

)"