#version 410

//layout (location = 0) in vec2 vertex_position;
layout (location = 0) in vec3 aPos; // Um vetor para as coordenadas
layout (location = 1) in vec2 texture_mapping;

out vec2 texture_coords;
uniform mat4 transform; // Recebe do OpenGl a matriz de transformação

void main () {
	texture_coords = texture_mapping;
	//gl_Position = vec4 (vertex_position, 0.0, 1.0);
	gl_Position = transform * vec4(aPos, 1.0);
	//gl_Position = vec4(aPos, 1.0); // OK Sully Grandão e de costas...
}
