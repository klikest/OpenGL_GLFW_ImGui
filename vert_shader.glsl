#version 430

layout (location=0) in vec3 position;  // coord
layout (location = 1) in vec3 aOffset;
layout (location = 2) in int voxel_id;


uniform mat4 v_matrix;
uniform mat4 proj_matrix;


out vec4 varyingColor;  // be interpolated by the rasterizer
out vec3 voxel_color;


vec3 hash31(float p)
{
    vec3 p3 = fract(vec3(p*21.2) * vec3(0.1031, 0.1030, 0.0973));
    p3 += dot(p3, p3.yzx + 33.33);
    return fract((p3.xxy + p3.yzz)*p3.zyx)+0.05;
}



void main(void) 
{

    mat4 mv_matrix = v_matrix;
    voxel_color = hash31(voxel_id);   
    
    gl_Position = proj_matrix * mv_matrix * vec4(position + aOffset, 1.0);  // right-to-left
    varyingColor = vec4(position, 1.0) * 0.5 + vec4(0.5, 0.5, 0.5, 0.5);
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