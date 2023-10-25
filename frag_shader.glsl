#version 430

in vec4 varyingColor;  // the same name
in vec3 voxel_color;

out vec4 FragColor;


uniform mat4 mv_matrix;
uniform mat4 proj_matrix;

void main(void) {
    //FragColor = vec4(voxel_color, 1.0f);
    FragColor = varyingColor;
}