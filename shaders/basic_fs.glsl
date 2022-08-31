#version 330 core
out vec4 finalColor;
  
in vec2 texCoord;

uniform sampler2D ourTexture;
uniform vec2 size_of_grid;

void main()
{
    finalColor = vec4(1 - texture(ourTexture, texCoord).xyz, 1);

    if(fract(texCoord.x * size_of_grid.x) < 0.08 || fract(texCoord.x * size_of_grid.x) > 0.92){
        finalColor = vec4(0.5, 0.5, 0.5, 1);
    }

    if(fract(texCoord.y * size_of_grid.y) < 0.08 || fract(texCoord.y * size_of_grid.y) > 0.92){
        finalColor = vec4(0.5, 0.5, 0.5, 1);
    }
}