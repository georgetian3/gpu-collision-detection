R"(

inline bool overlaps(const struct AABB a, const struct AABB b) {
    return (
        a.min.x <= b.max.x && a.max.x >= b.min.x &&
        a.min.y <= b.max.y && a.max.y >= b.min.y &&
        a.min.z <= b.max.z && a.max.z >= b.min.z
    );
}

#define ABS(x) (x >= 0 ? x : -x)

inline double3 midpoint(const struct AABB aabb) {
    return (aabb.min + aabb.max) / 2;
}

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

void narrow_phase_collision(__global struct Collidable* a, __global struct Collidable* b) {

    if (a->immovable && b->immovable) {
        return;
    }

    double3 normal;

    if (a->type == CUBOID && b->type == CUBOID) {
        // AABBs collide -> true collision
        double3 diff = midpoint(a->aabb) - midpoint(b->aabb);
        double3 mad = v_abs(diff);
        normal.x = 0;
        normal.y = 0;
        normal.z = 0;
        double3 da = a->aabb.min - b->aabb.max;
        double3 db = a->aabb.max - b->aabb.min;
        double3 ada = v_abs(da);
        double3 adb = v_abs(db);
        // if (ada.x < ada.y && ada.x < ada.z && ada.x < adb.x && ada.x < adb.y && ada.x < adb.z) {
        //     normal.x = 1;
        // } else if (adb.x < ada.y && adb.x < ada.z && adb.x < ada.x && adb.x < ada.y && ada.x < ada.z) {
        //     normal.x = 1;
        // } else if {

        // }
        normal.y = 1;
    } else if (a->type == SPHERE && b->type == SPHERE) {
        printf("ss\n");
        double3 diff = a->position - b->position;
        if (length2(diff) > a->radius + b->radius) {
            return;
        }
        normal = diff;
    } else if (a->type == SPHERE && b->type == CUBOID) {
        double3 dmin = a->position - b->aabb.min;
        double3 dmax = a->position - b->aabb.max;
        double3 abs_dmin = v_abs(dmin);
        double3 abs_dmax = v_abs(dmax);
        if (abs_dmin.x <= abs_dmin.y && abs_dmin.x <= abs_dmin.z && abs_dmin.x <= abs_dmax.x && abs_dmin.x <= abs_dmax.y && abs_dmin.x <= abs_dmax.z) {
            normal.x = -1;
        } else if (abs_dmin.y <= abs_dmin.x && abs_dmin.y <= abs_dmin.z && abs_dmin.y <= abs_dmax.x && abs_dmin.y <= abs_dmax.y && abs_dmin.y <= abs_dmax.z) {
            normal.y = -1;
        } else if (abs_dmin.z <= abs_dmin.x && abs_dmin.z <= abs_dmin.y && abs_dmin.z <= abs_dmax.x && abs_dmin.z <= abs_dmax.y && abs_dmin.z <= abs_dmax.z) {
            normal.z = -1;
        } else if (abs_dmax.x <= abs_dmin.x && abs_dmax.x <= abs_dmin.y && abs_dmax.x <= abs_dmin.z && abs_dmax.x <= abs_dmax.y && abs_dmax.x <= abs_dmax.z) {
            normal.x = 1;
        } else if (abs_dmax.y <= abs_dmin.x && abs_dmax.y <= abs_dmin.y && abs_dmax.y <= abs_dmin.z && abs_dmax.y <= abs_dmax.x && abs_dmax.y <= abs_dmax.z) {
            normal.y = 1;
        } else if (abs_dmax.z <= abs_dmin.x && abs_dmax.z <= abs_dmin.y && abs_dmax.z <= abs_dmin.z && abs_dmax.z <= abs_dmax.x && abs_dmax.z <= abs_dmax.y) {
            normal.z = 1;
        }
    } else if (a->type == CUBOID && b->type == SPHERE) {
        narrow_phase_collision(b, a);
        return;
    } else {
        printf("narrow_phase_collision ???\n");
    }

    if (!a->immovable) {
        double3 reflected = reflect(a->velocity, normal);
        printf("(%f %f %f) (%f %f %f) (%f %f %f)\n", a->velocity.x, a->velocity.y, a->velocity.z, normal.x, normal.y, normal.z, reflected.x, reflected.y, reflected.z);
        a->velocity = a->cor * reflect(a->velocity, normal);
    }

    if (!b->immovable) {
        double3 reflected = reflect(b->velocity, normal);
        printf("(%f %f %f) (%f %f %f) (%f %f %f)\n", b->velocity.x, b->velocity.y, b->velocity.z, normal.x, normal.y, normal.z, reflected.x, reflected.y, reflected.z);
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