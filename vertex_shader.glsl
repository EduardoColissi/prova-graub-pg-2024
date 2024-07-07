#version 330 core
layout (location = 0) in vec3 aPos; // Um vetor para as coordenadas
layout (location = 1) in vec3 aColor; // Um vetor para as cores
layout (location = 2) in vec2 aTexCoord; // Um vetor para as texturas
out vec3 ourColor; // Saída da cor para o fragment shader
out vec2 TexCoord; // Saída da textura para o fragment shader
uniform mat4 transform; // Recebe do OpenGl a matriz de transformação
//uniform float zoom; // OK !
void main()
{
    //gl_Position = vec4(0.5, 0.5, 0.5, 1.0);
    gl_Position = transform * vec4(aPos, 1.0);
    //gl_Position = transform * vec4(aPos, zoom); // Zoom não muito útil agora...
    ourColor = aColor; // Manda a cor que está no vetor 'aColor' para o fragment shader
    TexCoord = vec2(aTexCoord.x, aTexCoord.y); // Manda a info da textura que está no VAO(2) para o fragment shader
}
