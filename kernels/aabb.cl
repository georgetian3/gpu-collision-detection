R"(

#define MIN(a, b) a < b ? a : b
#define MAX(a, b) a < b ? b : a

__kernel void calculate_absolute_aabb(
    int i,
    int n,
    __global bool* processed,
    __global const struct Collidable* collidables,
    __global struct Node* nodes
) {
    if (i < 0) {
        i = get_global_id(0);
    }
    printf("iiii %d\n", i);
    if (nodes[i].left == -1) { // leaf node
        printf("leaf\n");
        const struct vec3 pos = collidables[i - (n - 1)].position;
        const struct AABB aabb = collidables[i - (n - 1)].relativeAABB;
        nodes[i].aabb.min = vec_add(pos, aabb.min);
        nodes[i].aabb.max = vec_add(pos, aabb.max);
    } else {
        struct AABB a, b, c;

        a = collidables[nodes[i].left ].relativeAABB;
        b = collidables[nodes[i].right].relativeAABB;

        c.min.x = MIN(a.min.x, b.min.x);
        c.min.y = MIN(a.min.y, b.min.y);
        c.min.z = MIN(a.min.z, b.min.z);
        c.max.x = MAX(a.max.x, b.max.x);
        c.max.y = MAX(a.max.y, b.max.y);
        c.max.z = MAX(a.max.z, b.max.z);

        nodes[i].aabb = c;
    }

    if (nodes[i].parent != -1) {
        calculate_absolute_aabb(nodes[i].parent, n, processed, collidables, nodes);
    }

}

)"