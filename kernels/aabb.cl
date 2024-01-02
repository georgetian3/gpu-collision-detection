R"(

// #define DEBUG

#ifdef DEBUG
struct vec3 {
    double x;
    double y;
    double z;
};

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
#endif

#define MIN(a, b) a < b ? a : b
#define MAX(a, b) a < b ? b : a

inline bool is_leaf(const struct Node* node) {
    return node->left == -1;
}

__kernel void calculate_relative_aabb(
    int n,
    __global const struct Collidable* collidables,
    __global struct Node* nodes
) {
    const int i = get_global_id(0);

    struct AABB a = collidables[nodes[i].left ].relativeAABB;
    struct AABB b = collidables[nodes[i].right].relativeAABB;

    struct AABB c;
    c.min.x = MIN(a.min.x, b.min.x);
    c.min.y = MIN(a.min.y, b.min.y);
    c.min.z = MIN(a.min.z, b.min.z);
    c.max.x = MAX(a.max.x, b.max.x);
    c.max.y = MAX(a.max.y, b.max.y);
    c.max.z = MAX(a.max.z, b.max.z);

    collidables[nodes[i]].relativeAABB = c;

}

__kernel void calculate_absolute_aabb(
    __global const struct Collidable* collidables
) {

}

)"