R"(

__kernel void calculate_absolute_aabb(
    int i,
    int n,
    __global int* processed,
    __global struct Collidable* collidables,
    __global struct Node* nodes
) {
    if (i < 0) {
        i = get_global_id(0);
    } else {
        if (!atomic_inc(processed + i)) {
            return;
        }
    }

    if (nodes[i].left == -1) { // leaf node
        const double3 pos = collidables[i - (n - 1)].position;
        const struct AABB aabb = collidables[i - (n - 1)].aabb;
        nodes[i].aabb.min = pos + aabb.min;
        nodes[i].aabb.max = pos + aabb.max;
    } else {

        struct AABB a = nodes[nodes[i].left ].aabb;
        struct AABB b = nodes[nodes[i].right].aabb;
        double3 aabb_min, aabb_max;

        aabb_min.x = min(a.min.x, b.min.x);
        aabb_min.y = min(a.min.y, b.min.y);
        aabb_min.z = min(a.min.z, b.min.z);
        aabb_max.x = max(a.max.x, b.max.x);
        aabb_max.y = max(a.max.y, b.max.y);
        aabb_max.z = max(a.max.z, b.max.z);

        nodes[i].aabb.min = aabb_min;
        nodes[i].aabb.max = aabb_max;
    }

    if (nodes[i].parent != -1) {
        calculate_absolute_aabb(nodes[i].parent, n, processed, collidables, nodes);
    }

}

)"