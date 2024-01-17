R"(

inline bool overlaps(const struct AABB a, const struct AABB b) {
    return (
        a.min.x <= b.max.x && a.max.x >= b.min.x &&
        a.min.y <= b.max.y && a.max.y >= b.min.y &&
        a.min.z <= b.max.z && a.max.z >= b.min.z
    );
}

#define ABS(x) (x < 0 ? -x : x)


__kernel void traverse(
    int i,
    int n,
    __global struct Collidable* collidables,
    __global struct Node* nodes
) {
    if (i < 0) {
        i = get_global_id(0);
    }
    
    struct Collidable collidable_i = collidables[i];
    struct Node node;

    struct Stack stack;
    stack_init(&stack);
    stack_push(&stack, 0);

    while (stack.size) {
        int node_i = stack_pop(&stack);
        node = nodes[node_i];
        struct AABB abs_aabb = absolute_aabb(collidable_i);
        // printf("%d popped %d (%f %f %f) (%f %f %f) (%f %f %f) (%f %f %f)\n", i,
        //     node_i, abs_aabb.min.x, abs_aabb.min.y, abs_aabb.min.z, 
        //     abs_aabb.max.x, abs_aabb.max.y, abs_aabb.max.z, 
        //     node.aabb.min.x, node.aabb.min.y, node.aabb.min.z, 
        //     node.aabb.max.x, node.aabb.max.y, node.aabb.max.z
        // );
        if (!overlaps(abs_aabb, node.aabb)) {
            // printf("%d popped %d no overlap\n", i, node_i);
            continue;
        }
        if (node.left == -1) { // leaf
            int j = node_i - (n - 1);
            struct Collidable collidable_j = collidables[j];
            if (j <= i) {
                continue;
            }
            printf("colliding %d %d\n", i, j);

            double e = 1 - 0.05;

            if (!collidables[i].immovable) {
                double new_velocity = e * -collidables[i].velocity.y;
                collidables[i].velocity.y = ABS(new_velocity) < 0.1 ? 0 : new_velocity;
            }

            if (!collidables[j].immovable) {
                double new_velocity = e * -collidables[j].velocity.y;
                collidables[j].velocity.y = ABS(new_velocity) < 0.1 ? 0 : new_velocity;
            }


            return;
        }

        stack_push(&stack, node.left );
        stack_push(&stack, node.right);
        // printf("%d pushed %d %d\n", i, node.left, node.right);

    }
    
}

)"