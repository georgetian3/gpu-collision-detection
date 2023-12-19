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

unsigned int morton3D(double x, double y, double z) {
    unsigned int xx = expandBits((unsigned int)(x * 1024));
    unsigned int yy = expandBits((unsigned int)(y * 1024));
    unsigned int zz = expandBits((unsigned int)(z * 1024));
    // printf("x %d y %d z %d xx %u yy %u zz %u", x, y, z, xx, yy, zz);
    return xx * 4 + yy * 2 + zz;
}

struct vec3 {
    double x;
    double y;
    double z;
};

enum Type {
    SPHERE,
    CUBE,
    RECTANGULAR_CUBOID
};


struct AABB {
    struct vec3 min;
    struct vec3 max;
};

struct Collidable {

    unsigned int type;
    unsigned int id;

    struct vec3 position;
    cl_ulong mortonCode;

    struct AABB relativeAABB;
    struct AABB absoluteAABB;

    union {
        double length;
        double radius;
        double xl;
    };

    double yl;
    double zl;

};

__kernel void mortonCodeAABB(
    __global const struct vec3* positions,
    __global unsigned int* types,
    __global double* xls,
    __global double* yls,
    __global double* zls,
    __global unsigned int* mortonCodes,
    __global struct AABB* aabbs
) {
    const struct vec3 position = positions[i];
    mortonCodes[i] = morton3D(position.x, position.y, position.z);
    struct AABB aabb;
    unsigned int type = types[i];
    switch (type) {
        case SPHERE: {
            const double radius = xls[i];
            aabb.min.x = position.x - radius;
            aabb.min.y = position.y - radius;
            aabb.min.z = position.z - radius;
            aabb.max.x = position.x + radius;
            aabb.max.y = position.y + radius;
            aabb.max.z = position.z + radius;
            break;
        }
        case CUBE: {
            break;
        }
        case RECTANGULAR_CUBOID: {
            break;
        }
    };
    aabbs[i] = aabb;
}

)"