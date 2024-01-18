R"(

__kernel void model_matrices(
    __global struct Collidable* collidables,
    __global float* sphere_matrices,
    __global float* cuboid_matrices
) {

    const int i = get_global_id(0);
    struct Collidable collidable = collidables[i];

    __global float* active, inactive;

    // calculate scale vector
    struct vec3 s;
    switch (collidable.type) {
        case SPHERE: {
            active = sphere_matrices;
            inactive = cuboid_matrices;
        case CUBE: {
            active = cuboid_matrices;
            inactive = sphere_matrices;
            s.x = collidable.length;
            s.y = collidable.length;
            s.z = collidable.length;
            break;
        }
        case CUBOID: {
            active = cuboid_matrices;
            inactive = sphere_matrices;
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

    *(active +  0) = s.x; *(active +  4) =   0; *(active +  8) =   0; *(active + 12) = p.x; 
    *(active +  1) =   0; *(active +  5) = s.y; *(active +  9) =   0; *(active + 13) = p.y; 
    *(active +  2) =   0; *(active +  6) =   0; *(active + 10) = s.z; *(active + 14) = p.z; 
    *(active +  3) =   0; *(active +  7) =   0; *(active + 11) =   0; *(active + 15) =   1;

    for (int i = 0; i < 16; i++) {
        *(inactive + i) = 0;
    }


}

)"