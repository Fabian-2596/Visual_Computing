#version 330 core

in vec3 colorVS;

//fragment shader output
out vec4 color;
//uniform GLfloat c;

void main(){
    color = vec4(colorVS.x, colorVS.y, colorVS.z, 1.0);
}

