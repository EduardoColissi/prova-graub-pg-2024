// UNISINOS
// Curso: Ciência da Computação - Híbrido
// Atividade Acadêmica - Processamento Gráfico
// Módulo 7
// Tarefa: Prova Grau B - Implementação de um jogo simples com Tilemap Isométrico
// Data: 03/07/2024
// Professor: Fernando Marson & Rossana Baptista Queiroz
// Alunos: Paulo Griebler Júnior & Rodrigo Ferreira Pires & Eduardo Colissi Wiceskoski
// Registros Acadêmicos: 1930669 & 1917485 & 1927367


/*•Implementar um mapa com no mínimo 15x15 tiles
•Elaborar uma maneira de codificar os mapas em ARQUIVOS DE CONFIGURAÇÃO
o Exemplo tileset tilesetIso.png com 7 tiles, que serão indexados de 0 a 6:
o Exemplo de um arquivo de configuração map.txt de um mapa 3x3 tiles com
57x114pixels:
tilesetIso.png 7 57 114
3 3
1 1 4
4 1 4
4 4 1
*/
//#include <iostream>

#ifndef MAP_H
#define MAP_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "Losango.h"



//#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h" // github.com/nothings/stb/blob/master/stb_image.h

using namespace std;

class Map {
    private:
        Log* log;
        //Config* config;

        vector<Tile> vecTiles; // Vetor dos tipos de Tiles existentes
        vector<vector<Losango>> vecLosangos; // Vetor de vetor de objetos Losango (cada objeto Losango tem um objeto Tile)

        Shader* shaderTile;
        unsigned int VAO;
        unsigned int texture;

        void init();
        void criaArrayDosTilesExistentes(); // Cria um array de tiles baseado no arquivo "tile_todos.png"

    public:
        Map();
        Map(string mapa);

        vector<Tile> getVecTiles();
        vector<vector<Losango>> getVecLosangos();

        void carregarMapa(string arquivo); // Carrega um mapa de um arquivo de configuração

        /*void constroiShaderTile();
        void constroiVAOTile();
        void carregaTexturaTile(); // Retorna o int da textura no atributo 'texture'
        void inicializaMapa();
        void atualizaMapaNaTela();*/

        ~Map();

};

#endif
