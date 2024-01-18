R"(

__kernel void model_matrices(
    __global struct Collidable* collidables,
    __global float* sphere_matrices,
    __global float* cuboid_matrices
) {

    const int i = get_global_id(0);
    struct Collidable collidable = collidables[i];

    bool is_sphere;

    // calculate scale vector
    struct vec3 s;
    switch (collidable.type) {
        case SPHERE: {
            is_sphere = true;
        case CUBE: {
            is_sphere = false;
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
            printf("Unsupported collidable type\n");
        }
    }

    struct vec3 p = collidable.position;

    int base = i * 16;

    if (is_sphere) {
        sphere_matrices[i +  0] = s.x; sphere_matrices[i +  4] =   0; sphere_matrices[i +  8] =   0; sphere_matrices[i + 12] = p.x; 
        sphere_matrices[i +  1] =   0; sphere_matrices[i +  5] = s.y; sphere_matrices[i +  9] =   0; sphere_matrices[i + 13] = p.y; 
        sphere_matrices[i +  2] =   0; sphere_matrices[i +  6] =   0; sphere_matrices[i + 10] = s.z; sphere_matrices[i + 14] = p.z; 
        sphere_matrices[i +  3] =   0; sphere_matrices[i +  7] =   0; sphere_matrices[i + 11] =   0; sphere_matrices[i + 15] =   1;
        for (int i = 0; i < 16; i++) {
            *(cuboid_matrices + i) = 0;
        }
    } else {
        cuboid_matrices[i +  0] = s.x; cuboid_matrices[i +  4] =   0; cuboid_matrices[i +  8] =   0; cuboid_matrices[i + 12] = p.x; 
        cuboid_matrices[i +  1] =   0; cuboid_matrices[i +  5] = s.y; cuboid_matrices[i +  9] =   0; cuboid_matrices[i + 13] = p.y; 
        cuboid_matrices[i +  2] =   0; cuboid_matrices[i +  6] =   0; cuboid_matrices[i + 10] = s.z; cuboid_matrices[i + 14] = p.z; 
        cuboid_matrices[i +  3] =   0; cuboid_matrices[i +  7] =   0; cuboid_matrices[i + 11] =   0; cuboid_matrices[i + 15] =   1;
        for (int i = 0; i < 16; i++) {
            *(sphere_matrices + i) = 0;
        }
    }


}

)"