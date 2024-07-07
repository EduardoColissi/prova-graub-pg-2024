// UNISINOS
// Curso: Ciência da Computação - Híbrido
// Atividade Acadêmica - Processamento Gráfico
// Módulo 7
// Tarefa: Prova Grau B - Implementação de um jogo simples com Tilemap Isométrico
// Data: 03/07/2024
// Professor: Fernando Marson & Rossana Baptista Queiroz
// Alunos: Paulo Griebler Júnior & Rodrigo Ferreira Pires & Eduardo Colissi Wiceskoski
// Registros Acadêmicos: 1930669 & 1917485 & 1927367


#include <glad/glad.h> // É necessário que a inclusão do glad.h seja feita antes da inclusão do glfw3 -- aliás o glad.h precisa ser incluído ANTES de qualquer outro arquivo cabeçalho que use os arquivos cabeçalhos do OpenGL (tipo GL/gl.h)
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <cmath> // para sin()
#include <vector>

#include "Shader.h"

//#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h" // github.com/nothings/stb/blob/master/stb_image.h

using namespace std;

const int MAX_TEXTURES = 2;

class Config {
    private:
        static Config* instance;
        // Computação do tempo para ajustar a taxa de frames por segundo (FPS)
        double tempoAnterior; //= 0.0;
        double tempoAtual; //= 0.0;

        GLFWwindow* window;

        unsigned int VAO;

        //unsigned int textureTile; // "tile_todos.png"
        //unsigned int texturePersona; // "viking.png"
        //vector<unsigned int> texture;
    public:
        unsigned int texture[];
    private:
        Config (); // Construtor privado - padrão Singleton
        static void framebuffer_size_callback(GLFWwindow* window, int width, int height);


        ~Config();

    public:
        static Config* getInstance();

        GLFWwindow* getWindow();
        Shader getShader();
        void setTempoAnterior(double tempoAnterior);
        double getTempoAnterior();
        void setTempoAtual(double tempoAtual);
        double getTempoAtual();
        void setVAO(unsigned int VAO);
        unsigned int getVAO();
        /*void setTexture(unsigned int texture[MAX_TEXTURES]);
        unsigned int* getTexture();*/ // REVER

        void vertices_VAO_Tile();
        void vertices_VAO_Persona();
        void carregaTexturas(vector<string> texturaNomes);

};



/*// Variáveis globais que organizam movimento do personagem:
int sprite_val = 0; // Varia de 0-15 ? // Para o Sully.png
const int SPRITE_VAL_MIN = 0;
const int SPRITE_VAL_MAX = 15;
float pos_x_val = 0.5; // Deslocamento do personagem no eixo X -- Varia de 0
const float POS_X_VAL_MIN = 0.0;
const float POS_X_VAL_MAX = 1.0;
float pos_y_val = 0.5; // Deslocamento do personagem no eixo Y
const float POS_Y_VAL_MIN = 0.0;
const float POS_Y_VAL_MAX = 0.5; // Não é 1.0 porque o fundo tem grama só até a metade...
float offsetx_val = 0.0; // Deslocamento da sprite no eixo X -- Varia de 0
const float OFFSETX_VAL_MIN = 0.0;
const float OFFSETX_VAL_MAX = 1.0;
float offsety_val = 0.0; // Deslocamento da sprite no eixo Y
const float OFFSETY_VAL_MIN = 0.0;
const float OFFSETY_VAL_MAX = 1.0;*/


