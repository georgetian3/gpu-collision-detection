R"(

#pragma OPENCL EXTENSION cl_khr_global_int32_base_atomics : enable
#pragma OPENCL EXTENSION cl_khr_local_int32_base_atomics : enable

#define MIN(a, b) a < b ? a : b
#define MAX(a, b) a < b ? b : a

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
        const struct vec3 pos = collidables[i - (n - 1)].position;
        const struct AABB aabb = collidables[i - (n - 1)].aabb;
        nodes[i].aabb.min = vec_add(pos, aabb.min);
        nodes[i].aabb.max = vec_add(pos, aabb.max);
    } else {
        struct AABB a, b;
        struct vec3 min, max;

        a = nodes[nodes[i].left ].aabb;
        b = nodes[nodes[i].right].aabb;

        min.x = MIN(a.min.x, b.min.x);
        min.y = MIN(a.min.y, b.min.y);
        min.z = MIN(a.min.z, b.min.z);
        max.x = MAX(a.max.x, b.max.x);
        max.y = MAX(a.max.y, b.max.y);
        max.z = MAX(a.max.z, b.max.z);

        printf("%d %d %d\n%f %f %f %f %f %f\n%f %f %f %f %f %f\n%f %f %f %f %f %f\n\n", nodes[i].parent, nodes[i].left, nodes[i].right, a.min.x, a.min.y, a.min.z, a.max.x, a.max.y, a.max.z, b.min.x, b.min.y, b.min.z, b.max.x, b.max.y, b.max.z, min.x, min.y, min.z, max.x, max.y, max.z);

        nodes[i].aabb.min = min;
        nodes[i].aabb.max = max;
    }

    if (nodes[i].parent != -1) {
        calculate_absolute_aabb(nodes[i].parent, n, processed, collidables, nodes);
    }

}

)"