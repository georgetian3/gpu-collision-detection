R"(

inline bool overlaps(const struct AABB a, const struct AABB b) {
    return (
        a.min.x <= b.max.x && a.max.x >= b.min.x &&
        a.min.y <= b.max.y && a.max.y >= b.min.y &&
        a.min.z <= b.max.z && a.max.z >= b.min.z
    );
}

#define ABS(x) (x >= 0 ? x : -x)

double3 reflect(double3 incident, double3 normal) {
    double3 reflected;
    double3 normalized = normalize(normal);
}


void narrow_phase_collision(__global struct Collidable* a, __global struct Collidable* b) {

    vec3 v_a, v_b;

    if (a->type == CUBOID && a->type == CUBOID) {
        
    } else if (a->type == SPHERE && b.type == SPHERE) {

    } else if (a->type == SPHERE && b->type == CUBOID) {


    } else if (a->type == CUBOID && b->type == SPHERE) {
        narrow_phase_collision(b, a);
        return;
    } else {
        printf("narrow_phase_collision ???\n");
    }

    if (!a->immovable) {
        a->velocity = v_a;
    }

    if (!b->immovable) {
        b->velocity = v_b;
    }
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

    // As OpenCL has limitations with recursion (cannot call `traverse` twice in itself)
    // therefore manual stack management was used. Recursion depth will not be greater
    // than the depth of the tree, i.e. number of bits in a morton code - 64.

    struct Stack stack;
    stack_init(&stack);
    stack_push(&stack, 0);

    while (stack.size) {
        int node_i = stack_pop(&stack);
        node = nodes[node_i];
        struct AABB abs_aabb = absolute_aabb(collidable_i);
        if (!overlaps(abs_aabb, node.aabb)) {
            continue;
        }
        if (node.left == -1) { // leaf
            int j = node_i - (n - 1);
            if (j <= i) {
                continue;
            }
            narrow_phase_collision(collidables + i, collidables + j);
            continue;
        }

        stack_push(&stack, node.left );
        stack_push(&stack, node.right);

    }
    
}

)"