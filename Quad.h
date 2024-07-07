// UNISINOS
// Curso: Ciência da Computação - Híbrido
// Atividade Acadêmica - Processamento Gráfico
// Módulo 7
// Tarefa: Prova Grau B - Implementação de um jogo simples com Tilemap Isométrico
// Data: 03/07/2024
// Professor: Fernando Marson & Rossana Baptista Queiroz
// Alunos: Paulo Griebler Júnior & Rodrigo Ferreira Pires & Eduardo Colissi Wiceskoski
// Registros Acadêmicos: 1930669 & 1917485 & 1927367

#include "Tile.h"

class Quad {
    private:
        int x; // Pos X (mais à esq.)
        int y; // Pos Y (mais inf.)
        int w; // largura
        int h; // altura
        float tX; // fator de transformação X (scale)
        float tY; // fator de transformação Y (scale)
        Tile tile; // Objeto Tile que será desenhado neste Quad
        bool ativo; // Indica se o Quad deve ser mostrado
        void init(); // Usado por todos os construtores


    public:
        Quad();
        Quad(int x, int y, int w, int h, float tX, float tY, Tile tile, bool ativo);

        ~Quad();

        void setTile(Tile tile);
        Tile getTile();
        int getX();
        int getY();
        int getW();
        int getH();
        float getTX();
        float getTY();
        void setAtivo(bool ativo);
        bool isAtivo();

        string toString();

};
