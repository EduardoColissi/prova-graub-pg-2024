#version 330 core
layout (location = 0) in vec3 aPos; // Um vetor para as coordenadas
layout (location = 1) in vec3 aColor; // Um vetor para as cores
layout (location = 2) in vec2 texture_mapping;

out vec3 ourColor; // Saída da cor para o fragment shader
out vec2 texture_coords;

uniform mat4 projection; // Recebe do OpenGl a matriz de projeção
uniform mat4 transform; // Recebe do OpenGl a matriz de transformação
void main()
{
    gl_Position = projection * transform * vec4(aPos, 1.0);
    ourColor = aColor; // Manda a cor que está no vetor 'aColor' para o fragment shader
    texture_coords = texture_mapping;
}
