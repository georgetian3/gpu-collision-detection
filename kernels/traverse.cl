R"(

inline bool overlaps(const struct AABB a, const struct AABB b) {
    // returns true if `a` and `b` overlap
    return (
        a.min.x <= b.max.x && a.max.x >= b.min.x &&
        a.min.y <= b.max.y && a.max.y >= b.min.y &&
        a.min.z <= b.max.z && a.max.z >= b.min.z
    );
}

#define ABS(x) (x >= 0 ? x : -x)

inline double3 v_abs(double3 v) {
    v.x = ABS(v.x);
    v.y = ABS(v.y);
    v.z = ABS(v.z);
    return v;
}

inline double3 reflect(double3 i, double3 n) {
    double l = length(n);
    if (l == 0.0) {
        return i;
    }
    if (l != 1.0) {
        n /= l;
    }

    return i - 2 * dot(i, n) * n;
}

double length2(double3 v) {
    return v.x * v.x + v.y * v.y + v.z * v.z;
}

int min_index(const double* arr, const int n) {
    // returns the index of element of minimum value in `arr`
    double curr_min = arr[0];
    int curr_min_index = 0;
    for (int i = 1; i < n; i++) {
        if (arr[i] < curr_min) {
            curr_min = arr[i];
            curr_min_index = i;
        }
    }
    return curr_min_index;
}

void exit_collidables(__global struct Collidable* a, __global struct Collidable* b, double3 direction) {
    // if two collidables are not just touching but are inside each other,
    // then move the two collidables such that they are just touching
    if (direction.x == 0.0 && direction.y == 0.0 && direction.z == 0.0) {
        return;
    }
    if (a->immovable && b->immovable) {
        return;
    } else if (a->immovable) {
        b->position -= direction;
    } else if (b->immovable) {
        a->position += direction;
    } else {
        a->position += direction / 2;
        b->position -= direction / 2;
    }
}

void narrow_phase_collision(__global struct Collidable* a, __global struct Collidable* b) {

    if (a->immovable && b->immovable) {
        return;
    }

    double3 normal, exit_dir;
    normal.x = 0;
    normal.y = 0;
    normal.z = 0;
    exit_dir.x = 0;
    exit_dir.y = 0;
    exit_dir.z = 0;

    if (a->type == CUBOID && b->type == CUBOID) {
        double3 diff1 = (a->position + a->aabb.min) - (b->position + b->aabb.max), diff2 = (a->position + a->aabb.max) - (b->position + b->aabb.min);
        double diffs[] = {ABS(diff1.x), ABS(diff1.y), ABS(diff1.z), ABS(diff2.x), ABS(diff2.y), ABS(diff2.z)};
        int mi = min_index(diffs, 6);
        normal[mi % 3] = mi > 2 ? 1 : -1;
        exit_dir = normal * (mi <= 2 ? diffs[mi] : -diffs[mi]);
    } else if (a->type == SPHERE && b->type == SPHERE) {
        double3 pos_diff = a->position - b->position;
        double length_diff = a->radius + b->radius - length(pos_diff);
        if (length_diff < 0) { // no true collision
            return;
        }
        normal = pos_diff;
        exit_dir = normal / length(pos_diff) * length_diff;
    } else if (a->type == SPHERE && b->type == CUBOID) {
        double3 dmin = v_abs(a->position - (b->position + b->aabb.min));
        double3 dmax = v_abs(a->position - (b->position + b->aabb.max));
        double diffs[] = {dmin.x, dmin.y, dmin.z, dmax.x, dmax.y, dmax.z};
        int mi = min_index(diffs, 6);
        normal[mi % 3] = mi > 2 ? 1 : -1;
        exit_dir = normal * diffs[mi];

    } else if (a->type == CUBOID && b->type == SPHERE) {
        narrow_phase_collision(b, a);
        return;
    }

    exit_collidables(a, b, exit_dir);

    if (!a->immovable) {
        a->velocity = a->cor * reflect(a->velocity, normal);
    }

    if (!b->immovable) {
        b->velocity = b->cor * reflect(b->velocity, -normal);
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