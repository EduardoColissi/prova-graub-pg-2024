// UNISINOS
// Curso: Ciência da Computação - Híbrido
// Atividade Acadêmica - Processamento Gráfico
// Módulo 7
// Tarefa: Prova Grau B - Implementação de um jogo simples com Tilemap Isométrico
// Data: 03/07/2024
// Professor: Fernando Marson & Rossana Baptista Queiroz
// Alunos: Paulo Griebler Júnior & Rodrigo Ferreira Pires & Eduardo Colissi Wiceskoski
// Registros Acadêmicos: 1930669 & 1917485 & 1927367

#include "Losango.h"

Losango::Losango() {
    init();
    log->funcaoN("Losango::Losango()");

    this->x = 0.0;
    this->y = 0.0;
    this->w = 0.0;
    this->h = 0.0;
    this->sX = 0.0;
    this->sY = 0.0;
    Tile tile = Tile();
    this->tile = tile;
    this->ativo = false;



};

Losango::Losango(float x, float y, float w, float h, float sX, float sY, Tile tile, bool ativo) {
    init();
    log->funcaoN("Losango::Losango(float "+to_string(x)+", float "+to_string(y)+", float "+to_string(w)+", float "+to_string(h)+", float "+to_string(sX)+", float "+to_string(sY)+", Tile tile, bool "+to_string(ativo)+")"); //error: invalid operands of types ‘const char [18]’ and ‘float’ to binary ‘operator+’

    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
    this->sX = sX;
    this->sY = sY;
    this->tile = tile;
    this->ativo = ativo;


};

// Usado por todos os construtores
void Losango::init() {
    log = Log::getInstance();
    log->funcaoN("void Losango::init()");

};



Losango::~Losango() {
};



float Losango::getX() {
    return x;
}

float Losango::getY() {
    return y;
}

float Losango::getW() {
    return w;
}

float Losango::getH() {
    return h;
}

float Losango::getSX() {
    return sX;
}

float Losango::getSY() {
    return sY;
}

Tile Losango::getTile() {
    return tile;
}

void Losango::setAtivo(bool ativo) {
    this->ativo = ativo;
}

bool Losango::isAtivo() {
    return ativo;
}

bool Losango::estaDentroDoLosango(Losango losango, double mx, double my) {
    Log::getInstance()->funcaoN("bool Losango::estaDentroDoLosango(Losango losango, double mx, double my)");

    // Algoritmo:
    //  - calcular as áreas dos 2 triângulos que compõe o losango a partir do ponto onde está o mouse
    // Se area(ABD) == area(ApB)+area(pBD)+area(ApD) então tem colisão! -- original
    //Se area(ABC) == area(ApB)+area(pBC)+area(ApC) então tem colisão! -- reescrito
    // Precisa obter os pontos A, B, C de 1 triângulo
    //pair<Triangulo> Losango::obter2TriangulosDoLosango(Losango losango)
    pair<Triangulo, Triangulo> par = obter2TriangulosDoLosango(losango);

    // Para o T0:
    Vertice A = par.first.a;
    Vertice B = par.first.b;
    Vertice C = par.first.c;
    Vertice p = criarVertice((float) mx, (float) my);

    // Calcula área ABC:
    float areaABC = areaTriangulo(par.first);

    // Calcula área ApB:
    Triangulo triApB = criarTriangulo(A, p, B);
    float areaApB = areaTriangulo(triApB);

    // Calcula área pBC:
    Triangulo tripBC = criarTriangulo(p, B, C);
    float areapBC = areaTriangulo(tripBC);

    // Calcula área ApC:
    Triangulo triApC = criarTriangulo(A, p, C);
    float areaApC = areaTriangulo(triApC);

    // Calcula se tem colisão no T0:
    if (areaABC == areaApB+areapBC+areaApC) return true;

    // Para o T1:
    Vertice D = par.second.a;
    Vertice E = par.second.b;
    Vertice F = par.second.c;

    // Calcula área DEF:
    float areaDEF = areaTriangulo(par.second);

    // Calcula área DpE:
    Triangulo triDpE = criarTriangulo(D, p, E);
    float areaDpE = areaTriangulo(triDpE);

    // Calcula área pEF:
    Triangulo tripEF = criarTriangulo(p, E, F);
    float areapEF = areaTriangulo(tripEF);

    // Calcula área DpF:
    Triangulo triDpF = criarTriangulo(D, p, F);
    float areaDpF = areaTriangulo(triDpF);

    // Calcula se tem colisão no T1:
    if (areaDEF == areaDpE+areapEF+areaDpF) return true;

    // Se chegou até aqui é pq não tem colisão:
    return false;
}

pair<Triangulo, Triangulo> Losango::obter2TriangulosDoLosango(Losango losango) {
     Log::getInstance()->funcaoN("pair<Triangulo> Losango::obter2TriangulosDoLosango(Losango losango)");

     // Algoritmo:
     // - A atributo x do Losango indica o centro do Losango no eixo X em coordenadas ortogonais (0-800)
     // - O atributo w do Losango indica o sua largura em unidades ortogonais (0-800)

     // - Então usa-se a regra abaixo:
    float Ax = losango.getX()-losango.getW()/2;
    float Ay = losango.getY();

    float Bx = losango.getX();
    float By = losango.getY()+losango.getH()/2;

    float Cx = losango.getX();
    float Cy = losango.getY()-losango.getH()/2;

    float Dx = losango.getX()+losango.getW()/2;
    float Dy = losango.getY();

    float Ex = Bx;
    float Ey = By;

    float Fx = Cx;
    float Fy = Cy;

    Vertice A = criarVertice(Ax, Ay);
    Vertice B = criarVertice(Bx, By);
    Vertice C = criarVertice(Cx, Cy);
    Vertice D = criarVertice(Dx, Dy);
    Vertice E = criarVertice(Ex, Ey);
    Vertice F = criarVertice(Fx, Fy);

    Triangulo T0 = criarTriangulo(A, B, C);
    Triangulo T1 = criarTriangulo(D, E, F);

    pair<Triangulo, Triangulo> par = {T0, T1};
    return par;

}


Vertice Losango::criarVertice(float x, float y) {
    Log::getInstance()->funcaoN("Vertice Losango::criarVertice(float x, float y)");
    Vertice v;
    v.x = x;
    v.y = y;
    return v;
}

Triangulo Losango::criarTriangulo(Vertice a, Vertice b, Vertice c) {
    Log::getInstance()->funcaoN("Triangulo Losango::criarTriangulo(Vertice a, Vertice b, Vertice c)");
    Triangulo t;
    t.a = a;
    t.b = b;
    t.c = c;
    return t;
}

//Cálculo de área do triângulo:
float Losango::areaTriangulo(Triangulo tri) {
    Log::getInstance()->funcaoN("float Losango::areaTriangulo(Triangulo tri)");

    //return abs(((V2x - V1x)*(V3y - V1y)-(V3x - V1x)*(V2y - V1y)) / 2)
    return abs(((tri.b.x - tri.a.x)*(tri.c.y - tri.a.y)-(tri.c.x - tri.a.x)*(tri.b.y - tri.a.y)) / 2);
}

pair<Triangulo, Triangulo> Losango::obterPontosDoLosangoParaCalculoDeVertices(float widthProj, float heightProj, float widthObj, float heightObj) {
    Log::getInstance()->funcaoN("pair<Triangulo> Losango::obterPontosDoLosangoParaCalculoDeVertices(float widthProj, float heightProj, float widthObj, float heightObj)");

        // Como escrever um vértice que mostra um losango ?
        // - desenhe 2 triângulos !
        // - precisa saber o tamanho do losango: eixo X = 100pixels | eixo Y = 60pixels
        // - precisa saber o tamanho da viewport (800x600)
        // - considera que vai desenhar a partir do centro da tela coordenada 400x300
        // - quantas vezes 800 cabe em 2 -> 2/800 = 0,0025
        // - width (largura - eixo X) x height (altura - eixo Y)
        // - widthProj = 800 | heightProj = 600
        // - widthObj = 100 | heightObj = 60
        // - rF_PixX = 2/800 = 0,0025
        // - rF_PixY = 2/600 = 0,0033
        // - ponto Ax -> 350pixel -> 0,0025x350 = 0,875 - 1,0 = -0,125
        // - ponto Ax -> ((width/2-widthObj/2)*rF_PixX)+1
        // - T0:
        // Ponto A (extrema esq./metade do valor de Y) Ax = (2/(800/2-50))+1 | Ay = 600/2
        // Ponto B (meio/cima) Bx = 800/2 | By = 600/2+30 (eixo Y 'cresce' para cima)
        // Ponto C (meio/baixo) Cx = 800/2 | Cy = 600/2-30
        // - T1:
        // Ponto D (extrema dir./metade do valor de Y) Dx = 800/2+50 | Dy = 600/2
        // Ponto E (meio/cima) Bx = 800/2 | By = 600/2+30 (eixo Y 'cresce' para cima)
        // Ponto F (meio/baixo) Cx = 800/2 | Cy = 600/2-30
        // Obs.: Pontos B/E e C/F são iguais por isso que poderia se usar EBO

    /*float widthProj = 800.0;
    float heightProj = 600.0;
    float widthObj = 100.0; //400.0; //100.0;
    float heightObj = 60.0;*/ // Deve receber por parâmetro ou por atributo da classe !!
    float rF_PixX = 2/widthProj; // = 0,0025
    float rF_PixY = 2/heightProj; // = 0,0033
    // - ponto Ax -> 350pixel -> 0,0025x350 = 0,875 - 1,0 = -0,125
    float Ax = ((widthProj/2-widthObj/2)*rF_PixX)-1;
    // - ponto Ay -> 300pixel -> 0,0033x300 = 0,99 - 1,0 = 0,11
    float Ay = ((heightProj/2)*rF_PixY)-1;
    //Bx = 800/2 | By = 600/2+30
    float Bx = (widthProj/2*rF_PixX)-1;
    float By = ((heightProj/2+heightObj/2)*rF_PixY)-1;
    //Cx = 800/2 | Cy = 600/2-30
    float Cx = (widthProj/2*rF_PixX)-1;
    float Cy = ((heightProj/2-heightObj/2)*rF_PixY)-1;
    //Dx = 800/2+50 | Dy = 600/2
    float Dx = ((widthProj/2+widthObj/2)*rF_PixX)-1;
    float Dy = Ay;
    float Ex = Bx;
    float Ey = By;
    float Fx = Cx;
    float Fy = Cy;

    Vertice A = criarVertice(Ax, Ay);
    Vertice B = criarVertice(Bx, By);
    Vertice C = criarVertice(Cx, Cy);
    Vertice D = criarVertice(Dx, Dy);
    Vertice E = criarVertice(Ex, Ey);
    Vertice F = criarVertice(Fx, Fy);

    Triangulo T0 = criarTriangulo(A, B, C);
    Triangulo T1 = criarTriangulo(D, E, F);

    pair<Triangulo, Triangulo> par = {T0, T1};
    return par;
}

string Losango::toString() {
    string str = string("Losango: [x:");
    str += to_string(x);
    str += ", y:";
    str += to_string(y);
    str += ", w:";
    str += to_string(w);
    str += ", h:";
    str += to_string(h);
    str += ", tX:";
    str += to_string(sX);
    str += ", tY:";
    str += to_string(sY);
    str += ", tile:";
    str += tile.toString();
    str += ", ativo:";
    str += to_string(ativo);
    str += "]";

    return str;

};



