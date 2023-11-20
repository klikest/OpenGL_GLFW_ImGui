#version 430

layout (location=0) in vec3 position;  // coord

uniform mat4 mv_matrix;
uniform mat4 proj_matrix;

out vec4 vcolor;  

void main(void) 
{
    vcolor = vec4(1, 1, 1, 1);    
    gl_Position = proj_matrix * mv_matrix * vec4(position, 1.0f);
}