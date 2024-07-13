// UNISINOS
// Curso: Ciência da Computação - Híbrido
// Atividade Acadêmica - Processamento Gráfico
// Módulo 7
// Tarefa: Prova Grau B - Implementação de um jogo simples com Tilemap Isométrico
// Data: 03/07/2024
// Professor: Fernando Marson & Rossana Baptista Queiroz
// Alunos: Paulo Griebler Júnior & Rodrigo Ferreira Pires & Eduardo Colissi Wiceskoski
// Registros Acadêmicos: 1930669 & 1917485 & 1927367

#ifndef PERSONA_H
#define PERSONA_H


#include <glad/glad.h> // É necessário que a inclusão do glad.h seja feita antes da inclusão do glfw3 -- aliás o glad.h precisa ser incluído ANTES de qualquer outro arquivo cabeçalho que use os arquivos cabeçalhos do OpenGL (tipo GL/gl.h)
#include <GLFW/glfw3.h>
//#include <GLFW/glfw3.h> // Para  GLFWwindow* //#error OpenGL header already included, remove this include, glad already provides it

#include "Map.h" // Para vector<vector<Losango>> vecLosangos;

using namespace std;

class Persona {
    private:
        Log* log;

        GLFWwindow* window;
        //Map* map;


        int x; // losango x
        int y; // losango y
        float w; // largura
        float h; // altura
        float sX; // fator de escala(scale) X
        float sY; // fator de escala(scale) Y
        float offsetX; // Deslocamento no eixo X dentro de "Viking.png" para achar a textura da Persona
        float offsetY;
        bool ativo; // Indica se a Persona deve ser mostrada
        void init(); // Usado por todos os construtores


    public:
        Persona(GLFWwindow* window);
        Persona(GLFWwindow* window, int x, int y, float w, float h, float sX, float sY, float offsetX, float offsetY, bool ativo);

        ~Persona();

        int getX();
        int getY();
        float getW();
        float getH();
        float getSX();
        float getSY();
        float getOffsetX();
        float getOffsetY();
        void setAtivo(bool ativo);
        bool isAtivo();

        void movimento(Map* map);

        string toString();

};

#endif
