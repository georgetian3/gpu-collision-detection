R"(

inline int common_prefix_length(__global struct Collidable* collidables, int n, int i, int j) {
    // computes the length of the longest common prefix of morton codes `a` and `b`
    if (j < 0 || j > n - 1) {
        return -1;
    }
    printf("i j m1 m2 %d %d %u %u %d\n", i, j, collidables[i].mortonCode, collidables[j].mortonCode, clz(collidables[i].mortonCode ^ collidables[j].mortonCode));
    return clz(collidables[i].mortonCode ^ collidables[j].mortonCode);
}

struct Node {
    int parent;
    int left;
    int right;
};

bool is_leaf(struct Node node) {
    return node.left == 0;
}


// // https://developer.nvidia.com/blog/parallelforall/wp-content/uploads/2012/11/karras2012hpg_paper.pdf
__kernel void construct_tree(
    int n,
    __global const struct Collidable* collidables,
    __global struct Node* nodes
) {
    printf("n cpl %d %d\n", n, common_prefix_length(collidables, n, 0, 1));
    const int i = get_global_id(0);
    const int d = (
        common_prefix_length(collidables, n, i, i + 1) - 
        common_prefix_length(collidables, n, i, i - 1)
    ) > 0 ? 1 : -1;

    const int d_min = common_prefix_length(collidables, n, i, i - d);
    int l_max = 2;
    while (common_prefix_length(collidables, n, i, i + l_max * d) > d_min) {
        l_max *= 2;
    }
    int l = 0;
    int t = l_max / 2;
    while (t > 0) {
        if (common_prefix_length(collidables, n, i, i + (l + t) * d) > d_min) {
            l += t;
        }
        t /= 2;
    }
    const int j = i + l * d;
    int d_n = common_prefix_length(collidables, n, i, j);
    int s = 0;
    
    double dividend = 1.0;
    do {
        dividend *= 2;
        t = ceil(l / dividend);
        printf("i t %d %d", i, t);
        if (common_prefix_length(collidables, n, i, i + (s + t) * d) > d_n) {
            s += t;
        }
    }
    while (t > 1);
    int g = i + s * d + min(d, 0);
    int left = (min(i, j) == g) ? g : g + n - 1;
    int right = (max(i, j) == g + 1) ? g + 1 : g + n;
    nodes[i].left = left;
    nodes[i].right = right;
    nodes[left].parent = i;
    nodes[right].parent = i;

}

)"