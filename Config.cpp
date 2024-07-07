// UNISINOS
// Curso: Ciência da Computação - Híbrido
// Atividade Acadêmica - Processamento Gráfico
// Módulo 7
// Tarefa: Prova Grau B - Implementação de um jogo simples com Tilemap Isométrico
// Data: 03/07/2024
// Professor: Fernando Marson & Rossana Baptista Queiroz
// Alunos: Paulo Griebler Júnior & Rodrigo Ferreira Pires & Eduardo Colissi Wiceskoski
// Registros Acadêmicos: 1930669 & 1917485 & 1927367

#include "Config.h"

Config* Config::instance = nullptr;



Config::Config() {
    cout << "Entrou em: Config::Config()" << endl; // Log

    // Computação do tempo para ajustar a taxa de frames por segundo (FPS)
    tempoAnterior = 0.0;
    tempoAtual = 0.0;


    // Inicializa OpenGL:
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    /*int nrAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
    cout << "Maximum nr of vertex attributes supported: " << nrAttributes << endl;*/ // Dá falha de segmentação...

    window = glfwCreateWindow(800, 600, "M7-Prova Grau B-Implementação de um jogo simples com Tilemap Isométrico", NULL, NULL);
    if (window == NULL) {
        cout << "###Erro: Falha na criação da janela GLFW !" << endl;
        glfwTerminate();
        exit(-1);
    }

    glfwMakeContextCurrent(window); // Informa para o GLFW fazer com a janela criada seja o contexto principal na thread atual.

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); // Define a função a ser chamada se a janela principal mudar de tamanho

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        cout << "###Erro: Falha na inicialização do GLAD !" << endl;
        exit(-1);
    }

    //glViewport(0, 0, 800, 600); // Define o tamanho da janela de renderização --> PRECISA ?
    //glViewport(0, 0, 400, 300); // Teste

    texture[MAX_TEXTURES]; // 2 Texturas "tile_todos.png" e "viking.png"

};

Config* Config::getInstance() {
    cout << "Entrou em: Config* Config::getInstance()" << endl; // Log

	if (instance == nullptr)
		{
		instance = new Config();
		}
	return instance;
};

void Config::setTempoAnterior(double tempoAnterior) {
    this->tempoAnterior = tempoAnterior;
}

double Config::getTempoAnterior() {
    return tempoAnterior;
}

void Config::setTempoAtual(double tempoAtual) {
    this->tempoAtual = tempoAtual;
}

double Config::getTempoAtual() {
    return tempoAtual;
}

void Config::setVAO(unsigned int VAO) {
    this->VAO = VAO;
}

unsigned int Config::getVAO() {
    return VAO;
}

/*void Config::setTexture(unsigned int texture[MAX_TEXTURES]) {
    this->texture = texture;
}

unsigned int* Config::getTexture() {
    return texture;
}*/ // REVER ---> error: invalid use of array with unspecified bounds   94 |     this->texture = texture;



GLFWwindow* Config::getWindow() {
    return window;
};


Config::~Config() {

};



// Ajusta o viewport para o tamanho da janela principal, no caso de ela ser maximizada ou mudar seu tamanho
void Config::framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
    //glViewport(0, 0, width/2, height/2); // Teste
}

Shader Config::getShader() {
    //Shader(const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr)
    Shader meuShader0("./vertex_shader.glsl", "./fragment_shader.glsl"); // Shader para o fundo
    //Shader meuShader1("./sprites_vs.glsl", "./sprites_fs.glsl"); // Shader para o personagem
    return meuShader0;
}

void Config::vertices_VAO_Tile() {
    cout << "Entrou em: Config::vertices_VAO_Tile()" << endl; // Log

    float vertices[] = {
         // positions          // texture coords (variam de 0.0 à 1.0 -- não podem ser negativas !)
        // Seguindo orientação anti-horário para facilitar a adição do eixo Z futuramente
        // Mudança na orientação dos eixo T para evitar de carregar as texturas de cabeça para baixo
        // X     Y     Z      R     G     B     S(X)  T(Y)
         1.0f,  1.0f, 0.0f,  1.0f, 1.0f, 0.0f,  1.0f, 0.0f, // sup./dir.
         1.0f, -1.0f, 0.0f,  1.0f, 1.0f, 0.0f,  1.0f, 1.0f, // inf./dir.
        -1.0f, -1.0f, 0.0f,  1.0f, 1.0f, 0.0f,  0.0f, 1.0f, // inf./esq.
        -1.0f,  1.0f, 0.0f,  1.0f, 1.0f, 0.0f,  0.0f, 0.0f  // sup./esq.
    };

    unsigned int indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };
    //unsigned int VBO, VAO, EBO;
    unsigned int VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute
    //void glVertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void * pointer);
    // index = ordem no array de informações (0 para vértices/1 para texturas)
    // size = tamanho da informação (para vértices = 3 / para texturas = 2)
    // stride = deslocamento entre este byte de informação (vértice ou textura) em relação ao próximo byte de informação de (vertice ou textura)
    // pointer = deslocamento entre as colunas de bytes de informação (vertice = 0/textura = 3*sizeof(float)) // Sempre: X*sizeof(tipo_em_uso)
    // Um float em C++ ocupa 4 bytes = 32 bits // Double ocupa 8 bytes (64 bits) ?
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);


    setVAO(VAO);
}


void Config::vertices_VAO_Persona() {
    cout << "Entrou em: Config::vertices_VAO_Persona()" << endl; // Log

    float vertices_PER[] = {
         // positions          // texture coords (variam de 0.0 à 1.0 -- não podem ser negativas !)
        // Seguindo orientação anti-horário para facilitar a adição do eixo Z futuramente
        // Mudança na orientação dos eixo T para evitar de carregar as texturas de cabeça para baixo
        // X     Y     Z      S(X)  T(Y)
         1.0f,  1.0f, 0.0f,   0.25f, 0.0f, // sup./dir. // 0.25 porque tem 16 figuras em um arquivo de textura --> 4x4
         1.0f, -1.0f, 0.0f,   0.25f, 0.25f, // inf./dir.
        -1.0f, -1.0f, 0.0f,   0.0f, 0.25f, // inf./esq.
        -1.0f,  1.0f, 0.0f,   0.0f, 0.0f  // sup./esq.
    };

    unsigned int indices_PER[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };
    unsigned int VBO_PER, VAO_PER, EBO_PER;
    glGenVertexArrays(1, &VAO_PER);
    glGenBuffers(1, &VBO_PER);
    glGenBuffers(1, &EBO_PER);

    glBindVertexArray(VAO_PER);

    glBindBuffer(GL_ARRAY_BUFFER, VBO_PER);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_PER), vertices_PER, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_PER);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_PER), indices_PER, GL_STATIC_DRAW);

    // position attribute
    //void glVertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void * pointer);
    // index = ordem no array de informações (0 para vértices/1 para texturas)
    // size = tamanho da informação (para vértices = 3 / para texturas = 2)
    // stride = deslocamento entre este byte de informação (vértice ou textura) em relação ao próximo byte de informação de (vertice ou textura)
    // pointer = deslocamento entre as colunas de bytes de informação (vertice = 0/textura = 3*sizeof(float)) // Sempre: X*sizeof(tipo_em_uso)
    // Um float em C++ ocupa 4 bytes = 32 bits // Double ocupa 8 bytes (64 bits) ?
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    /*// color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);*/ // Não tem cor aqui, só textura !
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

}

void Config::carregaTexturas(vector<string> texturaNomes) {
    cout << "Entrou em: Config::carregaTexturas()" << endl; // Log

    for (int i=0; i<texturaNomes.size(); i++) {
        // texture 1:
        //glGenTextures(1, &texture[i]);
        //glGenTextures(1, &(texture.at(i)));
        //void glGenTextures(GLsizei n, GLuint* textures);
        //Parameters
        //n  Specifies the number of texture names to be generated.
        //textures  Specifies an array in which the generated texture names are stored.
        glGenTextures(1, &texture[i]);
        glBindTexture(GL_TEXTURE_2D, texture[i]); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
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
        pathNome += texturaNomes.at(i);
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
            std::cout << "Failed to load texture: " << texturaNomes.at(i) << std::endl;
        }
        stbi_image_free(data);
    }
}



/*// Variáveis globais que organizam movimento do personagem:
int sprite_val = 0; // Varia de 0-15 ? // Para o Sully.png
const int SPRITE_VAL_MIN = 0;
const int SPRITE_VAL_MAX = 15;
float pos_x_val = 0.5; // Deslocamento do personagem no eixo X -- Varia de 0
const float POS_X_VAL_MIN = 0.0;
const float POS_X_VAL_MAX = 1.0;
float pos_y_val = 0.5; // Deslocamento do personagem no eixo Y
const float POS_Y_VAL_MIN = 0.0;
const float POS_Y_VAL_MAX = 0.5; // Não é 1.0 porque o fundo tem grama só até a metade...
float offsetx_val = 0.0; // Deslocamento da sprite no eixo X -- Varia de 0
const float OFFSETX_VAL_MIN = 0.0;
const float OFFSETX_VAL_MAX = 1.0;
float offsety_val = 0.0; // Deslocamento da sprite no eixo Y
const float OFFSETY_VAL_MIN = 0.0;
const float OFFSETY_VAL_MAX = 1.0;*/








