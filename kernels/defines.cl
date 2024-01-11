R"(

enum Type {
    SPHERE,
    CUBE,
    RECTANGULAR_CUBOID
};

struct vec3 {
    double x;
    double y;
    double z;
};

inline struct vec3 vec_add(const struct vec3 a, const struct vec3 b) {
    const struct vec3 r = {a.x + b.x, a.y + b.y, a.z + b.z};
    return r;
}

struct AABB {
    struct vec3 min;
    struct vec3 max;
};

struct Node {
    int parent;
    int left;
    int right;
    struct AABB aabb;
};

struct Collidable {

    unsigned int id;
    unsigned int type;

    struct vec3 position;
    ulong mortonCode;

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

inline int node_to_collidables_index(int i, int n) {
    return i - (n - 1);
}


)"