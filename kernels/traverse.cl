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
    const int node_i,
    __global struct Collidable* collidables,
    __global struct Node* nodes
) {
    if (i < 0) {
        i = get_global_id(0);
    }
    const struct Node node = nodes[node_i];
    if (!overlaps(collidables[i].aabb, node.aabb)) {
        return;
    }
    if (node.left == -1) { // leaf
        int j = node_i - (n - 1);
        if (j < i) {
            return;
        }
        printf("colliding %d %d\n", i, j);
        return;
    }
    // traverse(i, n, node.left , collidables, nodes);
    // traverse(i, n, node.right, collidables, nodes);

}

)"