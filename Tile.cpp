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

Tile::Tile() {
    init();
    log->funcaoN("");

    this->nome = "";
    this->offsetX = 0.0;
    this->offsetY = 0.0;
    this->caminhavel = false;
    this->fatal = false;
};

Tile::Tile(string nome, float offsetX, float offsetY, bool caminhavel, bool fatal) {
    init();
    log->funcaoN("");

    //  bool "<< caminhavel <<", bool "<< fatal <<"
    this->nome = nome;
    this->offsetX = offsetX;
    this->offsetY = offsetY;
    this->caminhavel = caminhavel;
    this->fatal = fatal;
};

void Tile::init() {
     log = Log::getInstance();
     log->funcaoN("");

}

Tile::~Tile() {

};

void Tile::setNome(string nome) {
    this->nome = nome;
}

string Tile::getNome() {
    return nome;
}

float Tile::getOffsetX() {
    return offsetX;
}

float Tile::getOffsetY() {
    return offsetY;
}

void Tile::setCaminhavel(bool caminhavel) {
    this->caminhavel = caminhavel;
}

bool Tile::isCaminhavel() {
    return caminhavel;
}

void Tile::setFatal(bool fatal) {
    this->fatal = fatal;
}

bool Tile::isFatal() {
    return fatal;
}

string Tile::toString() {
    string str = string("Tile: [nome:");
    str += nome;
    str += ", offsetX:";
    str += to_string(offsetX);
    str += ", offsetY:";
    str += to_string(offsetY);
    str += ", caminhavel:";
    str += to_string(caminhavel);
    str += ", fatal:";
    str += to_string(fatal);
    str += "]";

    return str;

};
