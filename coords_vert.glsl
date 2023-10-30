#version 430

layout (location=0) in vec3 position;  // coord
layout (location = 1) in vec3 aColor;

uniform mat4 mv_matrix;
uniform mat4 proj_matrix;

out vec4 vcolor;  

void main(void) 
{

    if (gl_VertexID < 6)
    {
        vcolor = vec4(1, 0, 0, 1.0f); 
    }

        if (gl_VertexID >= 6 && gl_VertexID < 12)
    {
        vcolor = vec4(0, 1, 0, 1.0f); 
    }

        if (gl_VertexID >= 12 && gl_VertexID < 18)
    {
        vcolor = vec4(0, 0, 1, 1.0f); 
    }
    
    gl_Position = proj_matrix * mv_matrix * vec4(position, 1.0f);
}






