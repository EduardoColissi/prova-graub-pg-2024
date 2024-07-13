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
    log->funcaoN("Map::Map()");
}

Map::Map(string mapa) {
    init();
    log->funcaoN("Map::Map(string"+mapa+")");


}

// Usado por todos os construtores
void Map::init() {
    log = Log::getInstance();
    log->funcaoN("void Map::init()");
    cout << "Entrou em: Map::init()" << endl; // Log

    //Config* config = Config::getInstance();

    criaArrayDosTilesExistentes();
}

vector<Tile> Map::getVecTiles() {
    return vecTiles;
}

vector<vector<Losango>> Map::getVecLosangos() {
    return vecLosangos;
}

// Cria um array de tiles baseado no arquivo "tile_todos.png"
void Map::criaArrayDosTilesExistentes() {
    log->funcaoN("void Map::criaArrayDosTilesExistentes()");

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

}

// Carrega um mapa de um arquivo de configuração
void Map::carregarMapa(string arquivo) {
    log->funcaoN("void Map::carregarMapa(string "+arquivo+")");
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

    // Popula os vector<vector<Losango>>:
    //Losango(int x, int y, int w, int h, float tX, float tY, Tile tile, bool ativo);
    float tw = 100.0;
    float th = 60.0;
    float sX = 1.0; //6.5; //5; // 1.0 = tamanho original - scale
    float sY = 1.0; //5;
    vector<Losango> vecLosangos2;
    for (int i = 0; i < tiles.size(); i++) { // Itera pela linha
        for (int j = 0; j < tiles.at(i).size(); j++) { // Itera pela coluna
            cout << "i =" << i << "| j =" << j << endl;
            //Tile(string nome, float offsetX, float offsetY, bool caminhavel, bool fatal);
            int tipo = stoi(tiles.at(i).at(j));
            if ((tipo >=0 ) && (tipo <= stoi(arqNumeroDeTiles))) {
                //Losango losango = Losango(j*tamX, i*tamY, tamX, tamY, tX, tY, vecTiles.at(tipo), true);
                //Losango losango = Losango(j, i, tamX, tamY, tX, tY, vecTiles.at(tipo), true);
                // Fórmula para posição de Tiles isométricos:
                float x = j*tw/2+i*tw/2;
                float y = j*th/2-i*th/2;
                Losango losango = Losango(x, y, tw, th, sX, sY, vecTiles.at(tipo), true);

                cout << "losango.toString() =" << losango.toString() << endl; // Debug
                vecLosangos2.push_back(losango);
            }
            else {
                cout << "###Erro: este número de tipo de tile não está cadastrado !" << endl;
                cout << "###PARADA DO PROGRAMA !!!" << endl;
                exit(-1);
            }
        }
        vecLosangos.push_back(vecLosangos2);
        vecLosangos2.clear();
    }
}

/*void Map::constroiShaderTile() {
    log->funcaoN("void Map::constroiShaderTile()");

    //shaderTile("./tile_vs.glsl", "./tile_fs.glsl"); //error: expression cannot be used as a function
    //shaderTile = Shader("./tile_vs.glsl", "./tile_fs.glsl");// Shader para o Tile // Compila, mas gera segmentation fault na execução

    Shader shaderTile2 = Shader("./tile_vs.glsl", "./tile_fs.glsl");
    shaderTile = &shaderTile2;
}*/

/*void Map::constroiVAOTile() {
    log->funcaoN("void Map::constroiVAOTile()");

    // set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float xi = -1.0f;
    float xf = 1.0f;
    float yi = -1.0f;
    float yf = 1.0f;
    float w = xf - xi;
    float h = yf - yi;
    float tw, th, tw2, th2;
    //int tileSetCols = 9, tileSetRows = 9;
    int tileSetCols = 3, tileSetRows = 3;
    float tileW, tileW2;
    float tileH, tileH2;
    int cx = -1, cy = -1;

    //cada tile tem altura 60 e largura 100
    //tw = w / (float)tmap->getWidth();
    tw = w / 100.0;
    th = tw / 2.0f;
    tw2 = th;
    th2 = th / 2.0f;
    tileW = 1.0f / (float) tileSetCols;
    tileW2 = tileW / 2.0f;
    tileH = 1.0f / (float) tileSetRows;
    tileH2 = tileH / 2.0f;

    cout << "tw=" << tw << " th=" << th << " tw2=" << tw2 << " th2=" << th2
        << " tileW=" << tileW << " tileH=" << tileH
        << " tileW2=" << tileW2 << " tileH2=" << tileH2
    << endl;


	/*float vertices[] = {
		// positions   // texture coords
		xi    , yi+th2, 0.0f, tileH2,   // left
		xi+tw2, yi    , tileW2, 0.0f,   // bottom
		xi+tw , yi+th2, tileW, tileH2,  // right
		xi+tw2, yi+th , tileW2, tileH,  // top
	};*/ // funcionava

    /*float vertices[] = {
        //X       Y      Z      R    G    B   S(X)   T(Y)
		xi,      yi+th2, 0.0,  1.0, 1.0, 0.0, 0.0f, tileH2,  // left -- cor amarela
		xi+tw2,  yi,     0.0,  1.0, 1.0, 0.0, tileW2, 0.0f,  // bottom
		xi+tw ,  yi+th2, 0.0,  1.0, 1.0, 0.0, tileW, tileH2, // right
		xi+tw2,  yi+th,  0.0,  1.0, 1.0, 0.0, tileW2,tileH,  // top
	};

	unsigned int indices[] = {
		0, 1, 3, // first triangle
		3, 1, 2  // second triangle
	};

	//unsigned int VBO, VAO, EBO;
    unsigned int VBO, EBO; // VAO é um atributo da classe
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);
    // cor
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// texture coord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);
}*/

/*void Map::carregaTexturaTile() {
    log->funcaoN("void Map::carregaTexturaTile()");

    string texturaNome = "tilemap_diamante.png";

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
    // set the texture wrapping parameters
    // void glTexParameteri( 	GLenum target,  	GLenum pname,  	GLint param);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method) // P/ Eixo S (X)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters // P/ Eixo T (Y)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
    // The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
    //unsigned char *data = stbi_load(FileSystem::getPath("resources/textures/container.jpg").c_str(), &width, &height, &nrChannels, 0); --> comando original github
    //unsigned char *data = stbi_load(filename, &x, &y, &n, 0); --> retirado de stb_image.h
    string pathNome = "./recursos/texturas/";
    pathNome += texturaNome;
    unsigned char *data = stbi_load(pathNome.c_str(), &width, &height, &nrChannels, 0); //
    if (data) {
        cout << "pathNome =" << pathNome << " | "; // Debug
        cout << "nrChannels =" << nrChannels << " | "; // Debug
        cout << "width =" << width << " | "; // Debug
        cout << "height =" << height << endl; // Debug
        (nrChannels == 3) ?
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data) :
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 800, 600, 0, GL_RGBA, GL_UNSIGNED_BYTE, data); // Tenta "esticar" a textura... Não dá certo !!!
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
        std::cout << "Failed to load texture: " << texturaNome << std::endl;
    }
    stbi_image_free(data);

}*/

/*void Map::inicializaMapa() {
    log->funcaoN("void Map::inicializaMapa()");

    constroiShaderTile();
    constroiVAOTile();
    carregaTexturaTile();
}*/

/*void Map::atualizaMapaNaTela() {
    log->funcaoN("void Map::atualizaMapaNaTela()");

    // Desenha o array de Tiles:
    glBindVertexArray(VAO);
    glBindTexture(GL_TEXTURE_2D, texture); // Ativa a textura do fundo
    shaderTile->use(); // O 'uso' do shader deve ser 'invocado' antes de iniciar as transformações -- senão o 'transform' não chegará no shader e será computado como '0' o que faz com que o personagem não apareça !
    float oriX = 0.92; // Pontos de origem para o desenho dos diamantes
    float oriY = 0.91;
    for (int i = 0; i < getVecLosangos().size(); i++) { // Itera pela linha
        for (int j = 0; j < getVecLosangos().at(i).size(); j++) { // Itera pela coluna
            cout << "i =" << i << "| j =" << j << endl;
            Losango losango = getVecLosangos().at(i).at(j);
            if (losango.isAtivo()) { // Só desenha o Losango se ele está ativo (on)

                glm::mat4 transform0 = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
                transform0 = glm::scale(transform0, glm::vec3(losango.getTX(), losango.getTY(), 0.0)); //
                //transform0 = glm::translate(transform0, glm::vec3(losango.getX()*1.01, losango.getY()*1.01, 0.0f)); //'pos_y_val' =1.01
                //transform0 = glm::translate(transform0, glm::vec3(j*1.01, i*1.01, 0.0f)); //'pos_y_val' =1.01
                //float tX = (float) j*0.01;
                //float tY = (float) i*0.01;
                //float tX = (float) 0.9+(j*0.01); // Assim temos losangos alinhados e empilhados estilo matriz 2D padrão
                //float tY = (float) 0.9+(i*0.01);

                float tX = (float) oriX+(j*0.0104); // Assim temos losangos alinhados e empilhados estilo matriz 2D padrão
                float tY = (float) oriY+(i*0.0104)+(j*0.0053);

                cout << "tX =" << tX << "| tY =" << tY << endl;
                transform0 = glm::translate(transform0, glm::vec3(tX, tY, 0.0f));
                //transform0 = glm::translate(transform0, glm::vec3(tY, tX, 0.0f));

                unsigned int transformLoc0 = glGetUniformLocation(shaderTile->ID, "transform");
                glUniformMatrix4fv(transformLoc0, 1, GL_FALSE, glm::value_ptr(transform0));
                unsigned int offsetx0 = glGetUniformLocation(shaderTile->ID, "offsetx");
                //void glUniform1f( 	GLint location,	GLfloat v0);
                //glUniform1f(transformAlfa0, 1.0);
                glUniform1f(offsetx0, losango.getTile().getOffsetX());
                unsigned int offsety0 = glGetUniformLocation(shaderTile->ID, "offsety");
                glUniform1f(offsety0, losango.getTile().getOffsetY());
                glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
            }
        }
        //oriX -= 2*(0.0104);
        //oriY -= 2*(0.0104);
        //oriY += oriY+0.005;
    }



}*/



Map::~Map() {
}
