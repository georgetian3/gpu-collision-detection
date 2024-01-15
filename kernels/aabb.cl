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
            print("returning\n");
            return;
        }
        print("continuing\n");
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

        nodes[i].aabb.min = min;
        nodes[i].aabb.max = max;
    }

    if (nodes[i].parent != -1) {
        printf("recursing\n");
        calculate_absolute_aabb(nodes[i].parent, n, processed, collidables, nodes);
    }

}

)"