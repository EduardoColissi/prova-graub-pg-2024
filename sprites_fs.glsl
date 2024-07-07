#version 410

in vec2 texture_coords;

uniform sampler2D sprite;
uniform float offsetx;
uniform float offsety;

out vec4 frag_color; 

void main () {
   //FragColor = texture(texture1, TexCoord);// O que se usa em "fragment_shader.glsl"
   frag_color = texture (sprite, vec2(texture_coords.x + offsetx, texture_coords.y + offsety));
//    frag_color = texture (sprite, texture_coords);
}
