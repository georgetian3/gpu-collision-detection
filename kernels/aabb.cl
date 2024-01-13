R"(

#pragma OPENCL EXTENSION cl_khr_global_int32_base_atomics : enable
#pragma OPENCL EXTENSION cl_khr_local_int32_base_atomics : enable

#define MIN(a, b) a < b ? a : b
#define MAX(a, b) a < b ? b : a

__kernel void calculate_absolute_aabb(
    int i,
    int n,
    __global int* processed,
    __global const struct Collidable* collidables,
    __global struct Node* nodes
) {

    if (i < 0) {
        i = get_global_id(0);
    } else {
        if (!atomic_inc(processed + i)) {
            return;
        }
    }


    struct Node node = nodes[i];
    printf("%d %d %d\n", node.parent, node.left, node.right);
    if (nodes[i].left == -1) { // leaf node
        const struct vec3 pos = collidables[i - (n - 1)].position;
        const struct AABB aabb = collidables[i - (n - 1)].aabb;
        nodes[i].aabb.min = vec_add(pos, aabb.min);
        nodes[i].aabb.max = vec_add(pos, aabb.max);
    } else {
        struct AABB a, b, c;

        a = collidables[nodes[i].left ].aabb;
        b = collidables[nodes[i].right].aabb;


        c.min.x = min(a.min.x, b.min.x);
        c.min.y = min(a.min.y, b.min.y);
        c.min.z = min(a.min.z, b.min.z);
        c.max.x = max(a.max.x, b.max.x);
        c.max.y = max(a.max.y, b.max.y);
        c.max.z = max(a.max.z, b.max.z);

        printf("%f %f %f %f %f %f\n%f %f %f %f %f %f\n%f %f %f %f %f %f\n\n", a.min.x, a.min.y, a.min.z, a.max.x, a.max.y, a.max.z, b.min.x, b.min.y, b.min.z, b.max.x, b.max.y, b.max.z, c.min.x, c.min.y, c.min.z, c.max.x, c.max.y, c.max.z);


        nodes[i].aabb = c;
    }

    if (nodes[i].parent != -1) {
        calculate_absolute_aabb(nodes[i].parent, n, processed, collidables, nodes);
    }

}

)"