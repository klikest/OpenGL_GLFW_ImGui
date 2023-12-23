#version 430

layout (location=0) in vec3 position;  // coord
layout (location = 1) in vec4 aOffset;
layout (location = 2) in int voxel_id;


uniform mat4 v_matrix;
uniform mat4 proj_matrix;

uniform float grid_size;
uniform float num_blank_dexels;

uniform vec3 lightPos;

out vec4 varyingColor;  // be interpolated by the rasterizer


vec3 hash31(float p)
{
    vec3 p3 = fract(vec3(p*21.2) * vec3(0.1031, 0.1030, 0.0973));
    p3 += dot(p3, p3.yzx + 33.33);
    return fract((p3.xxy + p3.yzz)*p3.zyx)+0.05;
}


vec3 lightColor;
vec3 objectColor;
vec3 lightDir;
vec4 pos;
vec3 pos_for_light;
vec3 normal;




void main(void) 
{


    if (gl_InstanceID > num_blank_dexels)
    {
        objectColor = vec3(0.75, 0.75, 0.3);
    }
    else
    {
        objectColor = vec3(0.8, 0.8, 0.8);
    }


    float size = 1/grid_size;
    mat4 mv_matrix = v_matrix; 
    vec4 pos = vec4(proj_matrix * mv_matrix * vec4(vec3((position.x + aOffset.x - 0.5)/size, (position.y + aOffset.y - 0.5)/size, (position.z*aOffset.w + aOffset.z)/size), 1.0));

    vec3 pos_for_light = vec3(aOffset.x/size, aOffset.y/size, aOffset.z/size);




    vec3 normal = vec3(0.0, 0.0, 0.0);
    vec3 lightDir = normalize(lightPos - pos_for_light);





    if (gl_VertexID < 6)
    {
        normal = vec3(0.0, 0.0, -1.0);
    }

    else if (gl_VertexID >= 6 && gl_VertexID < 12)
    {
        normal = vec3(1.0, 0.0, 0.0);
    }

    else if (gl_VertexID >= 12 && gl_VertexID < 18)
    {
        normal = vec3(0.0, 0.0, 1.0);
    }

    else if (gl_VertexID >= 18 && gl_VertexID < 24)
    {
        normal = vec3(-1.0, 0.0, 0.0);
    }

    else if (gl_VertexID >= 24 && gl_VertexID < 30)
    {
        normal = vec3(0.0, -1.0, 0.0);
    }

        else if (gl_VertexID >= 30 && gl_VertexID < 36)
    {
        normal = vec3(0.0, 1.0, 0.0);
    }



    lightColor = vec3(1.0, 1.0, 1.0);
    float diff = max(dot(normalize(normal), normalize(lightDir)), 0.0);
    vec3 diffuse = diff * lightColor;


    vec3 result = diffuse * objectColor + vec3(0.1, 0.1, 0.1);
    varyingColor = vec4(result, 1.0f);

 

    gl_Position = pos;  // right-to-left
    //varyingColor = vec4(position, 1.0) * 0.5 + vec4(0.5, 0.5, 0.5, 0.5);
}









// builds and returns a matrix that performs a rotation around the X axis
mat4 buildRotateX(float rad) {
    mat4 xrot = mat4(1.0, 0.0,      0.0,       0.0,
                     0.0, cos(rad), -sin(rad), 0.0,
                     0.0, sin(rad), cos(rad),  0.0,
                     0.0, 0.0,      0.0,       1.0);
    return xrot;
}

// builds and returns a matrix that performs a rotation around the Y axis
mat4 buildRotateY(float rad) {
    mat4 yrot = mat4(cos(rad),  0.0, sin(rad), 0.0,
                     0.0,       1.0, 0.0,      0.0,
                     -sin(rad), 0.0, cos(rad), 0.0,
                     0.0,       0.0, 0.0,      1.0);
    return yrot;
}

// builds and returns a matrix that performs a rotation around the Z axis
mat4 buildRotateZ(float rad) {
    mat4 zrot = mat4(cos(rad), -sin(rad), 0.0, 0.0,
                     sin(rad), cos(rad),  0.0, 0.0,
                     0.0,      0.0,       1.0, 0.0,
                     0.0,      0.0,       0.0, 1.0);
    return zrot;
}

// builds and returns a translation matrix
mat4 buildTranslate(float x, float y, float z) {
    mat4 trans = mat4(1.0, 0.0, 0.0, 0.0,
                      0.0, 1.0, 0.0, 0.0,
                      0.0, 0.0, 1.0, 0.0,
                      x,   y,   z,   1.0);
    return trans;
}