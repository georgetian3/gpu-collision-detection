R"(

inline int common_prefix_length(__global struct Collidable* collidables, int i, int j) {
    // computes the length of the longest common prefix of morton codes `a` and `b`
    return j == 0 ? -1 : clz(collidables[i].mortonCode ^ collidables[j].mortonCode);
}


struct Node {
    int parent;
    int left;
    int right;
};

bool is_leaf(struct Node node) {
    return node.left == 0;
}

// https://developer.nvidia.com/blog/parallelforall/wp-content/uploads/2012/11/karras2012hpg_paper.pdf
__kernel void construct_tree(
    int n,
    __global struct Collidable* collidables,
    __global struct Node* nodes
) {
    const int i = get_global_id(0);
    const int d = (
        common_prefix_length(collidables, i, i + 1) - 
        i == 0 ? -1 : common_prefix_length(collidables, i, i - 1)
    ) > 0 ? 1 : -1;

    const int d_min = common_prefix_length(collidables, i, i - d);
    int l_max = 2;
    while (common_prefix_length(collidables, i, i + l_max * d) > d_min) {
        l_max *= 2;
    }
    int l = 0;

    int t = l_max / 2;
    while (t > 0) {
        if (common_prefix_length(collidables, i, i + (l + t) * d) > d_min) {
            l += t;
        }
        t /= 2;
    }
    const int j = i + l * d;
    int d_n = common_prefix_length(collidables, i, j);
    int s = 0;
    
    double dividend = 1.0;
    do {
        dividend *= 2;
        t = ceil(l / dividend);
        if (common_prefix_length(collidables, i, i + (s + t) * d) > d_n) {
            s += t;
        }
    }
    while (t > 1);
    int g = i + s * d + min(d, 0);
    if (min(i, j) != g) {
        g += n - 1;
    }
    int left = (min(i, j) == g) ? g : g + n - 1;
    int right = (max(i, j) == g) ? g + 1 : g + n;

    nodes[i].left = left;
    nodes[i].right = right;
    nodes[left].parent = i;
    nodes[right].parent = i;

}

)"