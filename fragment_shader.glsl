#version 330 core
in vec3 ourColor; // Recebe a cor do vertex shader
in vec2 TexCoord; // Recebe a textura do vertex shader
out vec4 FragColor;
// texture samplers
uniform sampler2D texture1;
//uniform sampler2D texture2;
void main()
{
    //FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.2) ; // Interpola linearmente entre as 2 texturas (80% a 1ª (container2) e 20% a 2ª (awesomeface))
    //FragColor = texture(texture1, TexCoord); // Aqui em vez de mandar a cor, manda a textura
    //FragColor = texture(texture1, TexCoord).rgb * vec3(ourColor).xyz; error: value of type vec3 cannot be assigned to variable of type vec4
    //FragColor = vec4(vec3(texture(texture1, TexCoord).rgb * vec3(ourColor).xyz), 1.0);
    FragColor = vec4(1.0); // Debug
}
