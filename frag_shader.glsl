#version 430

in vec4 varyingColor;  // the same name


out vec4 FragColor;


uniform mat4 mv_matrix;
uniform mat4 proj_matrix;

void main(void) {
    FragColor = varyingColor;
}