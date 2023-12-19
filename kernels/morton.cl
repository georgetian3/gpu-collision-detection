R"(

long expandBits3(double v) {
    long u = ((long)(v * (1ull << 63))) >> 43; 
    u = (u | u << 32) & 0x1f00000000ffff;
    u = (u | u << 16) & 0x1f0000ff0000ff;
    u = (u | u << 8) & 0x100f00f00f00f00f;
    u = (u | u << 4) & 0x10c30c30c30c30c3;
    u = (u | u << 2) & 0x1249249249249249;
    return u;
}

long morton3D(double x, double y, double z) {
    return (expandBits3(x) << 2) | (expandBits3(y) << 1) | expandBits3(z);
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
    long mortonCode;

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

__kernel void mortonCodeAABB(__global struct Collidable* collidables) {
    printf("sizeof: %ld\n", sizeof(struct Collidable));
    const int i = get_global_id(0);
    struct Collidable collidable = collidables[i];
    const struct vec3 position = collidable.position;
    collidable.mortonCode = morton3D(position.x, position.y, position.z);
    switch (collidable.type) {
        case SPHERE: {
            const double radius = collidable.radius;
            collidable.relativeAABB.min.x = position.x - radius;
            collidable.relativeAABB.min.y = position.y - radius;
            collidable.relativeAABB.min.z = position.z - radius;
            collidable.relativeAABB.max.x = position.x + radius;
            collidable.relativeAABB.max.y = position.y + radius;
            collidable.relativeAABB.max.z = position.z + radius;
            break;
        }
        case CUBE: {
            break;
        }
        case RECTANGULAR_CUBOID: {
            break;
        }
    };
    collidables[i] = collidable;
}

)"