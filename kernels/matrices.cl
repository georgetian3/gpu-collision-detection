R"(

__kernel void model_matrices(
    __global struct Collidable* collidables,
    __global float* sphere_matrices,
    __global float* cuboid_matrices
) {

    const int i = get_global_id(0);
    struct Collidable collidable = collidables[i];

    bool is_sphere;
    printf("sizeof(double3): %d\n", sizeof(double3));

    // calculate scale vector
    double3 s;
    switch (collidable.type) {
        case SPHERE: {
            is_sphere = true;
            s.x = collidable.length;
            s.y = collidable.length;
            s.z = collidable.length;
            break;
        }
        case CUBOID: {
            is_sphere = false;
            s.x = collidable.xl;
            s.y = collidable.yl;
            s.z = collidable.zl;
            break;
        }
        default: {
            printf("Unsupported collidable type: %d\n", collidable.type);
        }
    }

    double3 p = collidable.position;

    int b = i * 16;

    if (is_sphere) {
        sphere_matrices[b + 0] = s.x; sphere_matrices[b + 4] =   0; sphere_matrices[b + 8] =   0; sphere_matrices[b +12] = p.x; 
        sphere_matrices[b + 1] =   0; sphere_matrices[b + 5] = s.y; sphere_matrices[b + 9] =   0; sphere_matrices[b +13] = p.y; 
        sphere_matrices[b + 2] =   0; sphere_matrices[b + 6] =   0; sphere_matrices[b +10] = s.z; sphere_matrices[b +14] = p.z; 
        sphere_matrices[b + 3] =   0; sphere_matrices[b + 7] =   0; sphere_matrices[b +11] =   0; sphere_matrices[b +15] =   1;
        for (int j = 0; j < 16; j++) {
            cuboid_matrices[b + j] = 0;
        }
    } else {
        cuboid_matrices[b + 0] = s.x; cuboid_matrices[b + 4] =   0; cuboid_matrices[b + 8] =   0; cuboid_matrices[b +12] = p.x; 
        cuboid_matrices[b + 1] =   0; cuboid_matrices[b + 5] = s.y; cuboid_matrices[b + 9] =   0; cuboid_matrices[b +13] = p.y; 
        cuboid_matrices[b + 2] =   0; cuboid_matrices[b + 6] =   0; cuboid_matrices[b +10] = s.z; cuboid_matrices[b +14] = p.z; 
        cuboid_matrices[b + 3] =   0; cuboid_matrices[b + 7] =   0; cuboid_matrices[b +11] =   0; cuboid_matrices[b +15] =   1;
        for (int j = 0; j < 16; j++) {
            sphere_matrices[b + j] = 0;
        }
    }


}

)"