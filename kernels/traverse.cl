R"(

inline bool overlaps(const struct AABB a, const struct AABB b) {
    return (
        a.min.x <= b.max.x && a.max.x >= b.min.x &&
        a.min.y <= b.max.y && a.max.y >= b.min.y &&
        a.min.z <= b.max.z && a.max.z >= b.min.z
    );
}


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
    stack_init(&stack, n * 2 - 1);

    stack_push(&stack, 0);

    while (stack.size) {
        int node_i = stack_pop(&stack);
        node = nodes[node_i];
        if (!overlaps(collidable_i.aabb, node.aabb)) {
            return;
        }
        if (node.left == -1) { // leaf
            int j = node_i - (n - 1);
            struct Collidable collidable_j = collidables[j];
            if (j < i) {
                return;
            }
            printf("colliding %d %d (%f %f %f) (%f %f %f)\n", i, j,
                collidable_i.position.x, collidable_i.position.y, collidable_i.position.z, 
                collidable_j.position.x, collidable_j.position.y, collidable_j.position.z
            );
            return;
        }

        stack_push(&stack, node.left );
        stack_push(&stack, node.right);

    }
    
}

)"