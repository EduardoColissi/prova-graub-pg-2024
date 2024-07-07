// UNISINOS
// Curso: Ciência da Computação - Híbrido
// Atividade Acadêmica - Processamento Gráfico
// Módulo 7
// Tarefa: Prova Grau B - Implementação de um jogo simples com Tilemap Isométrico
// Data: 03/07/2024
// Professor: Fernando Marson & Rossana Baptista Queiroz
// Alunos: Paulo Griebler Júnior & Rodrigo Ferreira Pires & Eduardo Colissi Wiceskoski
// Registros Acadêmicos: 1930669 & 1917485 & 1927367

#include "Map.h"

Map::Map() {

    init();
};

Map::Map(string mapa) {

    init();
};

// Usado por todos os construtores
void Map::init() {
    cout << "Entrou em: Map::init()" << endl; // Log

    //Config* config = Config::getInstance();

    criaArrayDosTilesExistentes();
};

vector<Tile> Map::getVecTiles() {
    return vecTiles;
};

vector<vector<Quad>> Map::getVecQuads() {
    return vecQuads;
};

// Cria um array de tiles baseado no arquivo "tile_todos.png"
void Map::criaArrayDosTilesExistentes() {
    cout << "Entrou em: Map::criaArrayDosTilesExistentes()" << endl; // Log

    // Sabe-se que o arquivo "tile_todos.png" está organizado da seguinte forma:
    //Col:      0       1     2
    //Lin:  0 água  cristal ametista
    //      1 grama mato    poço
    //      2 pedra areia   lava
    //vector<string> nomeTiles{"água", "cristal", "ametista", "grama", "mato", "poço", "pedra", "areia", "lava"};
    //Tile(string nome,         float offsetX, float offsetY, bool caminhavel, bool fatal);
    /*vecTiles.push_back(Tile("água",       0.0, 0.0, false, false)); // 0
    vecTiles.push_back(Tile("cristal",    0.33, 0.0, true, false)); // 1
    vecTiles.push_back(Tile("ametista",   0.66, 0.0, true, false)); // 2
    vecTiles.push_back(Tile("grama",      0.0, 0.33, true, false)); // 3
    vecTiles.push_back(Tile("mato",       0.33, 0.33, false, false)); // 4
    vecTiles.push_back(Tile("poço",       0.66, 0.33, true, true)); // 5
    vecTiles.push_back(Tile("pedra",      0.0, 0.66, true, false)); // 6
    vecTiles.push_back(Tile("areia",      0.33, 0.66, true, false)); // 7
    vecTiles.push_back(Tile("lava",       0.66, 0.66, true, true)); // 8*/ // Do arquivo "tile_todos.png"

    // Do arquivo: "tilemap_diamante.png" do Eduardo Colissi
    vecTiles.push_back(Tile("hack",        0.0, 0.0, false, false)); // 0 // Porque o mapa do Eduardo começa com o tile tipo 1 e não no tile tipo 0 como o meu
    vecTiles.push_back(Tile("lava0",        0.0, 0.0, true, true)); // 1
    vecTiles.push_back(Tile("lava1",        0.33, 0.0, true, true)); // 2
    vecTiles.push_back(Tile("lava2",        0.66, 0.0, true, true)); // 3
    vecTiles.push_back(Tile("agua0",        0.0, 0.33, false, false)); // 4
    vecTiles.push_back(Tile("agua1",        0.33, 0.33, false, false)); // 5
    vecTiles.push_back(Tile("agua2",        0.66, 0.33, false, false)); // 6
    vecTiles.push_back(Tile("grama",        0.0, 0.66, true, false)); // 7
    vecTiles.push_back(Tile("pedra",        0.33, 0.66, true, false)); // 8
    //vecTiles.push_back(Tile("lava",       0.66, 0.66, true, true)); // 9



    //vector<Tile> nomeTiles =

};

// Carrega um mapa de um arquivo de configuração
void Map::carregarMapa(string arquivo) {
    // - Obter string do arquivo:

        string strArq;
        ifstream Arq;
        // ensure ifstream objects can throw exceptions:
        Arq.exceptions (ifstream::failbit |ifstream::badbit);
        try {
            // open files
            Arq.open(arquivo);
            stringstream Stream;
            // read file's buffer contents into streams
            Stream << Arq.rdbuf();
            // close file handlers
            Arq.close();
            // convert stream into string
            strArq = Stream.str();
        }
        catch (std::ifstream::failure& e) {
            cout << "###Erro na leitura do arquivo " << arquivo << "| Motivo: " << e.what() << endl;
        }

    cout << "strArq =" << strArq << endl; // Debug

    // Separar as linhas e eliminar comentários:
    vector<string> linhas;

    int c0 = 0; // Início da string
    while(1) {
        //int c1 = strArq.find('\n'); // Procura por novas linhas
        int c1 = strArq.find("\n");
        cout << "c1 =" << c1 << endl; // Debug
        if (c1 != string::npos) {
            string lin = strArq.substr(c0, c1);
            cout << "lin =" << lin << endl; // Debug
            strArq = strArq.substr(c1+1);
            cout << "strArq =" << strArq << endl; // Debug
            //if (lin.find('#') != string::npos) linhas.push_back(lin);
            if (lin.find("#") == string::npos) linhas.push_back(lin);
            //c0 = c1;
        }
        else break;
    }

    for (int i = 0; i < linhas.size(); i++) {
        cout << "linhas.at(" << i << ") =" << linhas.at(i) << endl; // Debug
    }

    if (linhas.size() == 0) {
        cout << "###Erro: arquivo de mapa sem informação nenhuma !" << endl;
        cout << "###PARADA DO PROGRAMA !!!" << endl;
        exit(-1);
    }

    // Aqui vai ter só as linhas dos Tiles, sendo que a 1° é o nome do arquivo de texturas
    // Pega a 1° linha e acha o 1° espaço em branco para obter o nome do arquivo de texturas
    string linha0 = linhas.at(0);
    //string arqTexturasTiles = linhas.at(0).substr(0, linhas.at(0).find(" "));
    int c0_arq = 0;
    int c1_arq = linha0.find(" ");
    string arqTexturasTiles = linha0.substr(c0_arq, c1_arq);
    cout << "arqTexturasTiles = "<< arqTexturasTiles << endl; // Debug
    linha0 = linha0.substr(c1_arq+1);
    cout << "linha0 =" << linha0 << endl;  // Debug
    //string arqNumeroDeTiles = linhas.at(0).substr(0, linhas.at(0).find(" "));
    int c2_num = linha0.find(" ");
    cout << "c2_num =" << c2_num << endl;  // Debug
    string arqNumeroDeTiles = linha0.substr(0, c2_num);
    cout << "arqNumeroDeTiles = "<< arqNumeroDeTiles << endl; // Debug

     if (linhas.size() < 2) {
        cout << "###Erro: arquivo de mapa sem informações de posição de tiles" << endl;
        cout << "###PARADA DO PROGRAMA !!!" << endl;
        exit(-1);
    }

    vector<string> tiles_itens_lin;
    vector<vector<string>> tiles;
    // Itera pelas linhas
    for (int i = 1; i < linhas.size(); i++) {
        // Itera pelos ítens de uma linha
        int c0 = 0;
        string lin = linhas.at(i);
        while(1) {
            int c1 = lin.find(" "); // Procura por espaço em branco
            if (c1 != string::npos) {
                string tipoTile = lin.substr(c0, c1);
                cout << "tipoTile ="<< tipoTile << endl; // Debug
                tiles_itens_lin.push_back(tipoTile);
                lin = lin.substr(c1+1);
                //c0 = c1;
            }
            else break;
        }
        tiles.push_back(tiles_itens_lin);
        tiles_itens_lin.clear();
    }

    // Popula os vector<vector<Quad>>:
    //Quad(int x, int y, int w, int h, float tX, float tY, Tile tile, bool ativo);
    float tamX = 5;
    float tamY = 5;
    float tX = 5; // 1.0 = tamanho original - scale
    float tY = 5;
    vector<Quad> vecQuads2;
    for (int i = 0; i < tiles.size(); i++) { // Itera pela linha
        for (int j = 0; j < tiles.at(i).size(); j++) { // Itera pela coluna
            cout << "i =" << i << "| j =" << j << endl;
            //Tile(string nome, float offsetX, float offsetY, bool caminhavel, bool fatal);
            int tipo = stoi(tiles.at(i).at(j));
            if ((tipo >=0 ) && (tipo <= stoi(arqNumeroDeTiles))) {
                //Quad quad = Quad(j*tamX, i*tamY, tamX, tamY, tX, tY, vecTiles.at(tipo), true);
                Quad quad = Quad(j, i, tamX, tamY, tX, tY, vecTiles.at(tipo), true);
                cout << "quad.toString() =" << quad.toString() << endl; // Debug
                vecQuads2.push_back(quad);
            }
            else {
                cout << "###Erro: este número de tipo de tile não está cadastrado !" << endl;
                cout << "###PARADA DO PROGRAMA !!!" << endl;
                exit(-1);
            }
        }
        vecQuads.push_back(vecQuads2);
    }
};

void Map::MostraMapaNaTela() {
    // Constroí o VAO para os Quads do Mapa:
    config->vertices_VAO_Tile();

    // Carrega as texturas:
    vector<string> texturaNome = {"tiles_todos.png", "bonecos_v2.png",};
    //void Config::carregaTexturas(vector<string> texturaNomes)
    config->carregaTexturas(texturaNome);

    // Ativa a função 'atualizar_mapa' no main loop


}

void Map::AtualizarMapaParaMainLoop() {

}






Map::~Map() {
};
