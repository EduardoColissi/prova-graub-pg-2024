// UNISINOS
// Curso: Ciência da Computação - Híbrido
// Atividade Acadêmica - Processamento Gráfico
// Módulo 7
// Tarefa: Prova Grau B - Implementação de um jogo simples com Tilemap Isométrico
// Data: 03/07/2024
// Professor: Fernando Marson & Rossana Baptista Queiroz
// Alunos: Paulo Griebler Júnior & Rodrigo Ferreira Pires & Eduardo Colissi Wiceskoski
// Registros Acadêmicos: 1930669 & 1917485 & 1927367

/*- Construir classe que organiza as info de um tile:
    - tipo
    - offset X, Y no mapa de tiles
    - ação quando o personagem pisa nele
*/

#ifndef TILE_H
#define TILE_H

#include <iostream>
#include <string>
#include <vector>

#include "Log.h"
//#include "Config.h" // Não é mais necessário !

using namespace std;

class Tile {
    private:
        Log* log;

        string nome; // Nome da textura -- formato "nome_da_textura.png"
        float offsetX; // Deslocamento no eixo X dentro de "tiles_todos.png" para achar a textura do Tile
        float offsetY; // Deslocamento no eixo Y dentro de "tiles_todos.png" para achar a textura do Tile
        bool caminhavel; // Indica se o Quad é caminhável
        bool fatal; // Indica que se pisar neste Quad vai morrer
        // caminháveis: terra, areia, grama, pedra, cristal
        // não-caminháveis: mato, água
        // fatais: lava, poço

        void init();

    public:
        Tile();
        Tile(string nome, float offsetX, float offsetY, bool caminhavel, bool fatal);
        ~Tile();

        void setNome(string nome);
        string getNome();
        float getOffsetX();
        float getOffsetY();
        void setCaminhavel(bool caminhavel);
        bool isCaminhavel();
        void setFatal(bool fatal);
        bool isFatal();
        string toString();
};

#endif


/*- Conseguir conjunto de tiles (todos quadrados, com motivos variados "água", "grama", "lava", "pedra/muro", "poço", etc...
- Conseguir personagem em sprite com diferentes frames de movimento: "caminhada para dir/esq.", "parado", "morto", "pegando-fogo (caso caia na lava)..."
- Definir o esquema do mapa (posição dos tiles no mapa)


- Construir classe para o Personagem:
    - ações para fazer o personagem ir para:
        - dir.(L) -> troca de frames conforme caminha e deslocamento no mapa
        - mesma coisa para esq.(O), cima(N), baixo(S), NO, NL, SO, SL

- Construir classe Mapa - organiza as info do mapa:
    - ler a configuração do mapa de um arquivo
    - desenhar o mapa na tela
    - atualizar o desenho do mapa na tela
    - avaliar o novo movimento do personagem (suas consequências)
    - desenhar na tela essas consequências (morreu, pegou moeda, bateu no muro, etc)*/
