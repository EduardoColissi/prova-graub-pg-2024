// UNISINOS
// Curso: Ciência da Computação - Híbrido
// Atividade Acadêmica - Processamento Gráfico
// Módulo 7
// Tarefa: Prova Grau B - Implementação de um jogo simples com Tilemap Isométrico
// Data: 03/07/2024
// Professor: Fernando Marson & Rossana Baptista Queiroz
// Alunos: Paulo Griebler Júnior & Rodrigo Ferreira Pires & Eduardo Colissi Wiceskoski
// Registros Acadêmicos: 1930669 & 1917485 & 1927367

#ifndef LOSANGO_H
#define LOSANGO_H

#include <utility> // pair
#include "Tile.h"

class Vertice {
    public:
        float x;
        float y;
};

class Triangulo {
    public:
        Vertice a;
        Vertice b;
        Vertice c;
};

class Losango {
    private:
        Log* log;

        float x; // Pos X (centro do losango)
        float y; // Pos Y (centro do losango)
        float w; // largura
        float h; // altura
        float sX; // fator de escala(scale) X
        float sY; // fator de escala(scale) Y
        Tile tile; // Objeto Tile que será desenhado neste Losango
        bool ativo; // Indica se o Losango deve ser mostrado
        void init(); // Usado por todos os construtores


    public:
        Losango();
        Losango(float x, float y, float w, float h, float sX, float sY, Tile tile, bool ativo);

        ~Losango();

        void setTile(Tile tile);
        Tile getTile();
        float getX();
        float getY();
        float getW();
        float getH();
        float getSX();
        float getSY();
        void setAtivo(bool ativo);
        bool isAtivo();

        static Vertice criarVertice(float x, float y);
        static Triangulo criarTriangulo(Vertice a, Vertice b, Vertice c);
        static float areaTriangulo(Triangulo tri);
        static pair<Triangulo, Triangulo>obterPontosDoLosangoParaCalculoDeVertices(float widthProj, float heightProj, float widthObj, float heightObj);
        static bool estaDentroDoLosango(Losango losango, double mx, double my);
        static pair<Triangulo, Triangulo> obter2TriangulosDoLosango(Losango losango);

        string toString();

};

#endif
