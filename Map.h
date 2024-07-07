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

#include "Quad.h"

class Map {
    private:
        Config* config;

        vector<Tile> vecTiles; // Vetor dos tipos de Tiles existentes
        vector<vector<Quad>> vecQuads; // Vetor de vetor de objetos Quad (cada objeto Quad tem um objeto Tile)

        void init();
        void criaArrayDosTilesExistentes(); // Cria um array de tiles baseado no arquivo "tile_todos.png"

    public:
        Map();
        Map(string mapa);

        vector<Tile> getVecTiles();
        vector<vector<Quad>> getVecQuads();

        void carregarMapa(string arquivo); // Carrega um mapa de um arquivo de configuração
        void MostraMapaNaTela();
        void AtualizarMapaParaMainLoop();




        ~Map();

};
