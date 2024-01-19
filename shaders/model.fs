R"(
    
#version 330 core

in vec3 Normal;  
in vec3 FragPos;

out vec4 FragColor;

void main()
{
    FragColor = vec4(0.5, 0.5, 0.5, 1.0);
}

// #version 400 core

// // struct Light {
// //     vec3 position;

// //     vec3 ambient;
// //     vec3 diffuse;
// //     vec3 specular;

// //     float constant;
// //     float linear;
// //     float quadratic;
// // };

// // struct Material {
// //     sampler2D diffuse;
// //     sampler2D specular;
// //     float shininess;
// // };

// // uniform Light light;
// // uniform Material material;

// // uniform bool useColor;
// // uniform vec4 color;

// // uniform vec3 lightPos; 
// // uniform vec3 viewPos;
// // uniform vec3 lightColor;

// // in vec3 Normal;
// // in vec3 FragPos;

// out vec4 FragColor;


// void main() {

//     FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);

//     // vec3 norm = normalize(Normal);


//     // vec3 lightDir = normalize(lightPos - FragPos);

//     // vec3 ambient = light.ambient * color.rgb;
//     // vec3 diffuse = light.diffuse * (max(dot(norm, lightDir), 0.0) * color.rgb);
//     // vec3 specular = light.specular * (
//     //     pow(max(dot(normalize(viewPos - FragPos), reflect(-lightDir, norm)), 0.0), material.shininess) * color.rgb
//     // );

//     // FragColor = vec4(ambient + diffuse + specular, 1.0);

// } 

)"