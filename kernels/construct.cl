R"(

inline int common_prefix_length(const __global struct Collidable* collidables, int n, int i, int j) {
    // computes the length of the longest common prefix of morton codes `a` and `b`
    if (j < 0 || j > n - 1) {
        return -1;
    }
    return clz(collidables[i].mortonCode ^ collidables[j].mortonCode);
}


// https://developer.nvidia.com/blog/parallelforall/wp-content/uploads/2012/11/karras2012hpg_paper.pdf
__kernel void construct_tree(
    int n,
    __global const struct Collidable* collidables,
    __global struct Node* nodes
) {
    int i = get_global_id(0);
    // if (i != 0) {
    //     return;
    // }
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
    for (int t = l_max / 2; t >= 1; t /= 2) {
        if (common_prefix_length(collidables, n, i, i + (l + t) * d) > d_min) {
            l += t;
        }
    }
    int j = i + l * d;

    int d_n = common_prefix_length(collidables, n, i, j);
    int s = 0;

    int t;
    int dividend = 1;
    while (true) {
        dividend *= 2;
        t = ceil((double)l / dividend);
        if (common_prefix_length(collidables, n, i, i + (s + t) * d) > d_n) {
            s += t;
        }
        if (t == 1) {
            break;
        }
    }

    int g = i + s * d + min(d, 0);
    int left = (min(i, j) == g) ? (g + n - 1) : g;
    int right = (max(i, j) == g + 1) ? (g + n) : (g + 1);
    nodes[i].left = left;
    nodes[i].right = right;
    nodes[left].parent = i;
    nodes[right].parent = i;

}

)"