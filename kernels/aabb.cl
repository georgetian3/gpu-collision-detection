R"(

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
    } else if (!atomic_add(processed + i, 1)) {
        return;
    }


    struct Node node = nodes[i];
    printf("%d %d %d\n", node.parent, node.left, node.right);
    if (nodes[i].left == -1) { // leaf node
        printf("leaf\n");
        const struct vec3 pos = collidables[i - (n - 1)].position;
        const struct AABB aabb = collidables[i - (n - 1)].aabb;
        printf("%f %f %f %f %f %f %f %f %f\n", pos.x, pos.y, pos.z, aabb.min.x, aabb.min.y, aabb.min.z, aabb.max.x, aabb.max.y, aabb.max.z);
        nodes[i].aabb.min = vec_add(pos, aabb.min);
        nodes[i].aabb.max = vec_add(pos, aabb.max);
    } else {
        struct AABB a, b, c;

        a = collidables[nodes[i].left ].aabb;
        b = collidables[nodes[i].right].aabb;

        c.min.x = MIN(a.min.x, b.min.x);
        c.min.y = MIN(a.min.y, b.min.y);
        c.min.z = MIN(a.min.z, b.min.z);
        c.max.x = MAX(a.max.x, b.max.x);
        c.max.y = MAX(a.max.y, b.max.y);
        c.max.z = MAX(a.max.z, b.max.z);

        nodes[i].aabb = c;
    }

    if (nodes[i].parent != -1) {
        printf("recursing\n");
        calculate_absolute_aabb(nodes[i].parent, n, processed, collidables, nodes);
    }

}

)"