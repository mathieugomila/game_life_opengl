#version 330 core
layout (location = 0) in vec3 pos;

out vec2 texCoord;


void main(){
    gl_Position = vec4(pos, 1);
    texCoord = (pos.xy + 1) * 0.5;
}