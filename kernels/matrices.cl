R"(

__kernel void model_matrices(
    __global struct Collidable* collidables,
    __global float* matrices
) {

    const int i = get_global_id(0);
    struct Collidable collidable = collidables[i];

    // calculate scale vector
    struct vec3 s;
    switch (collidable.type) {
        case 0: // sphere
        case 1: { // cube
            s.x = collidable.length;
            s.y = collidable.length;
            s.z = collidable.length;
            break;
        }
        case 2: { // rectangularCuboid
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

    // base pointer
    int b = i * 16;

    matrices[b +  0] = s.x; matrices[b +  4] =   0; matrices[b +  8] =   0; matrices[b + 12] = p.x; 
    matrices[b +  1] =   0; matrices[b +  5] = s.y; matrices[b +  9] =   0; matrices[b + 13] = p.y; 
    matrices[b +  2] =   0; matrices[b +  6] =   0; matrices[b + 10] = s.z; matrices[b + 14] = p.z; 
    matrices[b +  3] =   0; matrices[b +  7] =   0; matrices[b + 11] =   0; matrices[b + 15] =   1;

}

)"