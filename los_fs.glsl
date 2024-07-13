#version 330 core
in vec3 ourColor; // Recebe a cor do vertex shader
in vec2 texture_coords;

uniform sampler2D sprite;
uniform float offsetx;
uniform float offsety;

out vec4 FragColor;
void main()
{
    //FragColor = vec4(ourColor, 1.0); // Debug
    FragColor = texture(sprite, vec2(texture_coords.x + offsetx, texture_coords.y + offsety));

}
