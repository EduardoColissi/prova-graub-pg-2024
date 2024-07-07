// UNISINOS
// Curso: Ciência da Computação - Híbrido
// Atividade Acadêmica - Processamento Gráfico
// Módulo 7
// Tarefa: Prova Grau B - Implementação de um jogo simples com Tilemap Isométrico
// Data: 03/07/2024
// Professor: Fernando Marson & Rossana Baptista Queiroz
// Alunos: Paulo Griebler Júnior & Rodrigo Ferreira Pires & Eduardo Colissi Wiceskoski
// Registros Acadêmicos: 1930669 & 1917485 & 1927367

#include "Quad.h"

Quad::Quad() {
    cout << "Entrou em: Quad::Quad()" << endl; // Log

    this->x = 0;
    this->y = 0;
    this->w = 0;
    this->h = 0;
    this->tX = 0.0;
    this->tY = 0.0;
    Tile tile = Tile();
    this->tile = tile;
    this->ativo = false;


    init();
};

Quad::Quad(int x, int y, int w, int h, float tX, float tY, Tile tile, bool ativo) {
    cout << "Entrou em: Quad(int "<< x <<", int "<< y <<", int "<< w <<", int "<< h <<", float "<< tX <<", float "<< tY <<", Tile tile, bool "<< ativo <<")" << endl; // Log

    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
    this->tX = tX;
    this->tY = tY;
    this->tile = tile;
    this->ativo = ativo;

    init();
};

// Usado por todos os construtores
void Quad::init() {
    cout << "Entrou em: Quad::init()" << endl; // Log

};



Quad::~Quad() {
};



int Quad::getX() {
    return x;
}

int Quad::getY() {
    return y;
}

int Quad::getW() {
    return w;
}

int Quad::getH() {
    return h;
}

float Quad::getTX() {
    return tX;
}

float Quad::getTY() {
    return tY;
}

Tile Quad::getTile() {
    return tile;
}

void Quad::setAtivo(bool ativo) {
    this->ativo = ativo;
}

bool Quad::isAtivo() {
    return ativo;
}



string Quad::toString() {
    string str = string("Quad: [x:");
    str += to_string(x);
    str += ", y:";
    str += to_string(y);
    str += ", w:";
    str += to_string(w);
    str += ", h:";
    str += to_string(h);
    str += ", tX:";
    str += to_string(tX);
    str += ", tY:";
    str += to_string(tY);
    str += ", tile:";
    str += tile.toString();
    str += ", ativo:";
    str += to_string(ativo);
    str += "]";

    return str;

};



