R"(

#define MIN(a, b) a < b ? a : b
#define MAX(a, b) a < b ? b : a

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