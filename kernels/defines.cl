R"(

enum Type {
    SPHERE,
    CUBOID
};

struct AABB {
    double3 min;
    double3 max;
};

struct Node {
    struct AABB aabb;
    int parent;
    int left;
    int right;
} __attribute__((packed));

struct Collidable {

    double3 position;
    double3 velocity;
    struct AABB aabb;

    ulong mortonCode;
    union {
        double length;
        double radius;
        double xl;
    };
    double yl;
    double zl;
    double mass;
    double cor;

    unsigned int id;
    unsigned int type;

    int immovable;
} __attribute__((packed));

inline int node_to_collidables_index(int i, int n) {
    return i - (n - 1);
}

struct Stack {
    int data[64];
    int size;
    int max_size;
};

void stack_init(struct Stack* stack) {
    stack->size = 0;
    stack->max_size = 64;
}

void stack_push(struct Stack* stack, int obj) {
    if (stack->size >= stack->max_size) {
        printf("Exceeded stack size\n");
        return;
    }
    stack->data[stack->size] = obj;
    stack->size++;
}

int stack_pop(struct Stack* stack) {
    if (stack->size == 0) {
        printf("Popping empty stack\n");
        return -1;
    }
    stack->size--;
    return stack->data[stack->size];
}

struct AABB absolute_aabb(const struct Collidable collidable) {
    struct AABB aabb;
    aabb.min = collidable.aabb.min + collidable.position;
    aabb.max = collidable.aabb.max + collidable.position;
    return aabb;
}

)"