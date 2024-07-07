// UNISINOS
// Curso: Ciência da Computação - Híbrido
// Atividade Acadêmica - Processamento Gráfico
// Módulo 5
// Tarefa: Controle e Animação de Sprites
// Data: 02/07/2024
// Professora: Rossana Baptista Queiroz
// Aluno: Paulo Griebler Júnior
// Registro Acadêmico: 1930669

//Compilar com: g++ prova_grau_B.cpp -o prova_grau_B src/glad.c -I include -L/usr/lib/x86_64-linux-gnu/ -L/usr/lib64 -lGLEW -lGL -lX11 -lglfw -lrt -lm -ldl
// Rodar com: ./prova_grau_B

// Texturas grátis:
// https://craftpix.net/freebies/


#include <glad/glad.h> // É necessário que a inclusão do glad.h seja feita antes da inclusão do glfw3 -- aliás o glad.h precisa ser incluído ANTES de qualquer outro arquivo cabeçalho que use os arquivos cabeçalhos do OpenGL (tipo GL/gl.h)
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <cmath> // para sin()
//#include <filesystem>

#include "Shader.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h" // github.com/nothings/stb/blob/master/stb_image.h

using namespace std;

// Variáveis globais que organizam movimento do personagem:
int sprite_val = 0; // Varia de 0-15 ? // Para o Sully.png
const int SPRITE_VAL_MIN = 0;
const int SPRITE_VAL_MAX = 15;
//float pos_x_val = 0.5; // Deslocamento do personagem no eixo X -- Varia de 0
float pos_x_val = 1.0; // Deslocamento do personagem no eixo X -- Varia de 0
const float POS_X_VAL_MIN = 0.0;
//const float POS_X_VAL_MAX = 1.0;
const float POS_X_VAL_MAX = 2.0;
//float pos_y_val = 0.5; // Deslocamento do personagem no eixo Y
float pos_y_val = 1.0; // Deslocamento do personagem no eixo Y
const float POS_Y_VAL_MIN = 0.0;
//const float POS_Y_VAL_MAX = 1.0;
const float POS_Y_VAL_MAX = 2.0;
float offsetx_val = 0.0; // Deslocamento da sprite no eixo X -- Varia de 0
const float OFFSETX_VAL_MIN = 0.0;
const float OFFSETX_VAL_MAX = 1.0;
float offsety_val = 0.0; // Deslocamento da sprite no eixo Y
const float OFFSETY_VAL_MIN = 0.0;
const float OFFSETY_VAL_MAX = 1.0;

// Computação do tempo para ajustar a taxa de frames por segundo (FPS)
double tempo_anterior = 0.0;
double tempo_atual = 0.0;

// Ajusta o viewport para o tamanho da janela principal, no caso de ela ser maximizada ou mudar seu tamanho
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
    //glViewport(0, 0, width/2, height/2); // Teste
}

// Processa os eventos disparados
void processInput(GLFWwindow* window) {

    // Pressionou a tecla ESC
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) glfwSetWindowShouldClose(window, true);

    /*// Muda a sprite do personagem:
    if(glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) { // Deve REDUZIR o valor da sprite do personagem
        if(sprite_val <= SPRITE_VAL_MIN) { // Verifica se já não está no valor mínimo
            cout << "###AVISO: 'sprite_val' já está no valor mínimo que é: " << SPRITE_VAL_MIN << endl;
        }
        else {
            sprite_val--;
            cout << "'sprite_val' =" << sprite_val << endl;
        }
    }
    if(glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) { // Deve AUMENTAR o valor da sprite do personagem
        if(sprite_val >= SPRITE_VAL_MAX) { // Verifica se já não está no valor máximo
            cout << "###AVISO: 'sprite_val' já está no valor máximo que é: " << SPRITE_VAL_MAX << endl;
        }
        else {
            sprite_val++;
            cout << "'sprite_val' =" << sprite_val << endl;
        }

    }

    // Muda o offsetx do personagem:
    if(glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) { // Deve REDUZIR o valor do offsetx do personagem -- Deve movimentar o personagem para ESQ.
        if(pos_x_val <= POS_X_VAL_MIN) {
            cout << "###AVISO: 'pos_x_val' já está no valor mínimo que é: " << POS_X_VAL_MIN << endl;
        }
        else {
            if(offsetx_val <= OFFSETX_VAL_MIN) { // Verifica se já não está no valor mínimo
                cout << "###AVISO: 'offsetx_val' já está no valor mínimo que é: " << OFFSETX_VAL_MIN << endl;
                offsetx_val = OFFSETX_VAL_MAX;
            }
            else {
                //offsetx_val--;
                offsetx_val = offsetx_val - 0.25;

            }
            pos_x_val -= 0.05;
            cout << "'offsetx_val' =" << offsetx_val << endl;
            cout << "'pos_x_val' =" << pos_x_val << endl;
        }
    }
    if(glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) { // Deve AUMENTAR o valor do offsetx do personagem
        if(offsetx_val >= OFFSETX_VAL_MAX) { // Verifica se já não está no valor máximo
            cout << "###AVISO: 'offsetx_val' já está no valor máximo que é: " << OFFSETX_VAL_MAX << endl;
        }
        else {
            //offsetx_val++;
            offsetx_val = offsetx_val + 0.25;
            cout << "'offsetx_val' =" << offsetx_val << endl;
        }
    }

    // Muda o offsety do personagem:
    if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) { // Deve REDUZIR o valor do offsety do personagem
        if(offsety_val <= OFFSETY_VAL_MIN) { // Verifica se já não está no valor mínimo
            cout << "###AVISO: 'offsety_val' já está no valor mínimo que é: " << OFFSETY_VAL_MIN << endl;
        }
        else {
            //offsety_val--;
            offsety_val = offsety_val - 0.25;
            cout << "'offsety_val' =" << offsety_val << endl;
        }
    }
    if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) { // Deve AUMENTAR o valor do offsety do personagem
        if(offsety_val >= OFFSETY_VAL_MAX) { // Verifica se já não está no valor máximo
            cout << "###AVISO: 'offsety_val' já está no valor máximo que é: " << OFFSETY_VAL_MAX << endl;
        }
        else {
            //offsety_val++;
            offsety_val = offsety_val + 0.25;
            cout << "'offsety_val' =" << offsety_val << endl;
        }
    }*/



    // Muda o offsetx do personagem:
    if(glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) { // Deve REDUZIR o valor do offsetx do personagem -- Deve movimentar o personagem para ESQ.
        if(pos_x_val <= POS_X_VAL_MIN) {
            cout << "###AVISO: 'pos_x_val' já está no valor mínimo que é: " << POS_X_VAL_MIN << endl;
        }
        else {
            pos_x_val -= 0.05;
            cout << "'pos_x_val' =" << pos_x_val << endl;
        }
    }
    if(glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) { // Deve AUMENTAR o valor do offsetx do personagem
        if(pos_x_val >= POS_X_VAL_MAX) {
            cout << "###AVISO: 'pos_x_val' já está no valor mínimo que é: " << POS_X_VAL_MAX << endl;
        }
        else {
            pos_x_val += 0.05;
            cout << "'pos_x_val' =" << pos_x_val << endl;
        }
    }

    // Muda o offsety do personagem:
    if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) { // Deve REDUZIR o valor do pos_y_val
        if(pos_y_val <= POS_Y_VAL_MIN) {
            cout << "###AVISO: 'pos_y_val' já está no valor mínimo que é: " << POS_Y_VAL_MIN << endl;
        }
        else {
            pos_y_val -= 0.05;
            cout << "'pos_y_val' =" << pos_y_val << endl;
        }

    }
    if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) { // Deve AUMENTAR o valor do pos_y_val
        if(pos_y_val >= POS_Y_VAL_MAX) {
            cout << "###AVISO: 'pos_y_val' já está no valor mínimo que é: " << POS_Y_VAL_MAX << endl;
        }
        else {
            pos_y_val += 0.05;
            cout << "'pos_y_val' =" << pos_y_val << endl;
        }

    }


}

void mensagem_de_inicio() {
    cout << "Para mudar a sprite do personagem tecle '1' ou '2'." << endl;
    cout << "Para mudar o offsetx do personagem tecle 'LEFT' ou 'RIGHT'." << endl;
    cout << "Para mudar o offsety do personagem tecle 'UP' ou 'DOWN'." << endl;
}

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    /*int nrAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
    cout << "Maximum nr of vertex attributes supported: " << nrAttributes << endl;*/ // Dá falha de segmentação...

    GLFWwindow* window = glfwCreateWindow(800, 600, "M5-Controle e Animação de Sprites", NULL, NULL);
    if (window == NULL) {
        cout << "###Erro: Falha na criação da janela GLFW !" << endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window); // Informa para o GLFW fazer com a janela criada seja o contexto principal na thread atual.

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); // Define a função a ser chamada se a janela principal mudar de tamanho

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        cout << "###Erro: Falha na inicialização do GLAD !" << endl;
        return -1;
    }

    //glViewport(0, 0, 800, 600); // Define o tamanho da janela de renderização --> PRECISA ?
    //glViewport(0, 0, 400, 300); // Teste


    //Shader(const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr)
    //Shader meuShader0("./vertex_shader.glsl", "./fragment_shader.glsl"); // Shader para o fundo
    Shader meuShader0("./sprites_vs.glsl", "./sprites_fs.glsl"); // Shader para o Tile
    Shader meuShader1("./sprites_vs.glsl", "./sprites_fs.glsl"); // Shader para o personagem

    // VERTICES E VAO PARA O FUNDO:
    //cada tile tem altura 60 e largura 100
    /*float vertices_FUN[] = {
         // positions          // texture coords (variam de 0.0 à 1.0 -- não podem ser negativas !)
        // Seguindo orientação anti-horário para facilitar a adição do eixo Z futuramente
        // Mudança na orientação dos eixo T para evitar de carregar as texturas de cabeça para baixo
        // X     Y     Z      S(X)  T(Y)
         1.0f,  1.0f, 0.0f,   1.0f, 0.0f, // sup./dir.
         1.0f, -1.0f, 0.0f,   1.0f, 1.0f, // inf./dir.
        -1.0f, -1.0f, 0.0f,   0.0f, 1.0f // inf./esq.
        //-1.0f,  1.0f, 0.0f,   0.0f, 0.0f  // sup./esq.
    };

    //unsigned int indices_FUN[] = {
    //    0, 1, 3, // first triangle
    //    1, 2, 3  // second triangle
    //};
    //unsigned int VBO_FUN, VAO_FUN, EBO_FUN;
    unsigned int VBO_FUN, VAO_FUN;
    glGenVertexArrays(1, &VAO_FUN);
    glGenBuffers(1, &VBO_FUN);
    //glGenBuffers(1, &EBO_FUN);

    glBindVertexArray(VAO_FUN);

    glBindBuffer(GL_ARRAY_BUFFER, VBO_FUN);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_FUN), vertices_FUN, GL_STATIC_DRAW);

    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_FUN);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_FUN), indices_FUN, GL_STATIC_DRAW);

    // position attribute
    //void glVertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void * pointer);
    // index = ordem no array de informações (0 para vértices/1 para texturas)
    // size = tamanho da informação (para vértices = 3 / para texturas = 2)
    // stride = deslocamento entre este byte de informação (vértice ou textura) em relação ao próximo byte de informação de (vertice ou textura)
    // pointer = deslocamento entre as colunas de bytes de informação (vertice = 0/textura = 3*sizeof(float)) // Sempre: X*sizeof(tipo_em_uso)
    // Um float em C++ ocupa 4 bytes = 32 bits // Double ocupa 8 bytes (64 bits) ?
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    //glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    //glEnableVertexAttribArray(1); // Não tem cor aqui, só textura !
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);*/


    // set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float xi = -1.0f;
    float xf = 1.0f;
    float yi = -1.0f;
    float yf = 1.0f;
    float w = xf - xi;
    float h = yf - yi;
    float tw, th, tw2, th2;
    int tileSetCols = 9, tileSetRows = 9;
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


	float vertices[] = {
		// positions   // texture coords
		xi    , yi+th2, 0.0f, tileH2,   // left
		xi+tw2, yi    , tileW2, 0.0f,   // bottom
		xi+tw , yi+th2, tileW, tileH2,  // right
		xi+tw2, yi+th , tileW2, tileH,  // top
	};
	unsigned int indices[] = {
		0, 1, 3, // first triangle
		3, 1, 2  // second triangle
	};

	unsigned int VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);
	// texture coord attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)(2 * sizeof(float)));
	glEnableVertexAttribArray(1);


    /*float WIDTH = 1.0;
    float HEIGHT = 1.0;

    GLfloat vertices[] = {
        // Positions                             // Colors
        WIDTH * 0.25f, HEIGHT * 0.75f, +0.0f,    0.0f, 0.0f, 1.0f,
        WIDTH * 0.50f, HEIGHT * 0.25f, +0.0f,    1.0f, 0.0f, 0.0f,
        WIDTH * 0.75f, HEIGHT * 0.75f, +0.0f,    0.0f, 1.0f, 0.0f,
    };

    glm::mat4 proj = glm::ortho(0.0f, (float)WIDTH, (float)HEIGHT, 0.0f, -1.0f, 1.0f);


    GLuint VAO_FUN, VBO;
    glGenVertexArrays( 1, &VAO_FUN );
    glGenBuffers( 1, &VBO );
    glBindVertexArray( VAO_FUN );
    glBindBuffer( GL_ARRAY_BUFFER, VBO);
    glBufferData( GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW );
    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof( GLfloat ), ( GLvoid * ) 0 );
    glEnableVertexAttribArray( 0 );
    glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof( GLfloat ), (GLvoid *)(3*sizeof(float)) );
    glEnableVertexAttribArray( 1 );

    glBindVertexArray( 0 );*/ // Não deu certo !!!



    // VERTICES E VAO PARA O PERSONAGEM

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




    // load and create a texture
    // -------------------------
    const int MAX_TEXTURES = 2;
    string texturaNome[MAX_TEXTURES] = {
        "tilemap_diamante.png",
        "Viking.png",
    };

    unsigned int texture[MAX_TEXTURES];
    for (int i=0; i<MAX_TEXTURES; i++) {
        // texture 1:
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
        pathNome += texturaNome[i];
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
            std::cout << "Failed to load texture: " << texturaNome[i] << std::endl;
        }
        stbi_image_free(data);
    }

    //glm::mat4 projection = glm::ortho(0.0, 800.0, 0.0, 600.0, -1.0, 1.0); // Parece sem efeito aqui

    // Mostra a mensagem de início -- teclas, funcionamento...
    mensagem_de_inicio();

    //double glfwGetTime(void) This function returns the value of the GLFW timer. Unless the timer has been set using glfwSetTime, the timer measures time elapsed since GLFW was initialized.
    //Returns  The current value, in seconds, or zero if an error occurred.
    //Remarks  This function may be called from secondary threads.
    //Note  The resolution of the timer is system dependent, but is usually on the order of a few micro- or nanoseconds. It uses the highest-resolution monotonic time source on each supported platform.


    tempo_anterior = glfwGetTime();
    cout << "tempo_anterior =" << tempo_anterior << endl;


    glEnable(GL_BLEND); // Permitem que a camada transparente do canal alfa de um PNG possa realmente ser 'transparente' ao encontrar se sobrepor à outras camadas de outras sprites que não são transparentes
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    // Loop de renderização
    while(!glfwWindowShouldClose(window)) { // Loop que mantém o desenho da janela principal --> Se glfwWindowShouldClose(window) retorna 'true' o loop pára e o programa encerra
        glm::mat4 projection = glm::ortho(0.0, 800.0, 0.0, 600.0, -1.0, 1.0);

        // Entradas:
        tempo_atual = glfwGetTime();
        //cout << "tempo_atual =" << tempo_atual << endl;
        //tempo_anterior =0.326702
        //tempo_atual =0.326723
        //tempo_atual =0.327641
        //cout << "tempo_atual - tempo_anterior =" << (tempo_atual - tempo_anterior) << endl;
        if ((tempo_atual - tempo_anterior) > 0.1) { // Avalia o tempo decorrido para autorizar o processo de inputs (e mudar as sprites do personagem)
            processInput(window); // Processa os eventos ocorridos
            tempo_anterior = tempo_atual;
        }



        // Comandos de renderização:
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        //glClear(GL_COLOR_BUFFER_BIT); // Aplica as cores acima ao buffer de cor -- poderia aplicar as cores acima a outros buffers (GL_DEPTH_BUFFER_BIT OU GL_STENCIL_BUFFER_BIT)
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Usa GL_DEPTH_BUFFER_BIT para apagar o buffer das texturas


        // Desenha o fundo:
        //glBindVertexArray(VAO_FUN);
        glBindVertexArray(VAO);
        glBindTexture(GL_TEXTURE_2D, texture[0]); // Ativa a textura do fundo
        glm::mat4 transform0 = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        // Não aplica nenhuma outra transformação aqui pois esse é o fundo...
        //transform0 = glm::rotate(transform0, glm::radians(180.0f), glm::vec3(0.0, 0.0, 1.0)); // Tá de cabeça para baixo a imagem -- deixa de cabeça para cima ==> resolvido na inversão da coordenada T(Y) em vertices[]
        /*transform0 = glm::scale(transform0, glm::vec3(0.5, 0.5, 0.0)); // usa 1.235 em todos os eixos para não distorcer a imagem, embora vá perder algumas pedaços nas bordas laterais
        meuShader0.use();
        unsigned int transformLoc0 = glGetUniformLocation(meuShader0.ID, "transform");
        glUniformMatrix4fv(transformLoc0, 1, GL_FALSE, glm::value_ptr(transform0));
        //unsigned int transformAlfa0 = glGetUniformLocation(meuShader0.ID, "canalAlfa");
        //void glUniform1f( 	GLint location,	GLfloat v0);
        //glUniform1f(transformAlfa0, 1.0); // 1.0 - Canal Alfa totalmente ativo !!!
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);*/ // DEL
        transform0 = glm::scale(transform0, glm::vec3(5.0, 5.0, 0.0)); //
        //transform0 = glm::translate(transform0, glm::vec3(pos_x_val, pos_y_val, 0.0f));
        transform0 = glm::translate(transform0, glm::vec3(pos_x_val, pos_y_val, 0.0f));
        unsigned int transformLoc0 = glGetUniformLocation(meuShader0.ID, "transform");
        glUniformMatrix4fv(transformLoc0, 1, GL_FALSE, glm::value_ptr(transform0));

        glUniform1i(glGetUniformLocation(meuShader0.ID, "sprite"), sprite_val); //
        unsigned int offsetx0 = glGetUniformLocation(meuShader0.ID, "offsetx");
        //void glUniform1f( 	GLint location,	GLfloat v0);
        //glUniform1f(transformAlfa0, 1.0);
        glUniform1f(offsetx0, offsetx_val);
        unsigned int offsety0 = glGetUniformLocation(meuShader0.ID, "offsety");
        glUniform1f(offsety0, offsety_val);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);



        // Desenha o personagem:
        glBindVertexArray(VAO_PER);
        glBindTexture(GL_TEXTURE_2D, texture[1]); // Ativa a textura do fundo
        // NÃO FUNCIONA USAR TRANSFORM AQUI PORQUE O PERSONAGEM USA UM SHADER DIFERENTE DO FUNDO QUE NÃO TEM A COMPUTAÇÃO (AINDA) DE UMA TRANSFORMAÇÃO -- SÓ ORGANIZA O OFFSET DENTRO DA SPRITE
        /*glm::mat4 transform1 = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        transform1 = glm::scale(transform1, glm::vec3(0.01, 0.01, 0.0)); // usa 1.235 em todos os eixos para não distorcer a imagem, embora vá perder algumas pedaços nas bordas laterais
        transform1 = glm::rotate(transform1, glm::radians(180.0f), glm::vec3(0.0, 0.0, 1.0)); // Tá de cabeça para baixo a imagem -- deixa de cabeça para cima


        unsigned int transformLoc1 = glGetUniformLocation(meuShader1.ID, "transform");
        glUniformMatrix4fv(transformLoc1, 1, GL_FALSE, glm::value_ptr(transform1));*/


        //Aqui deve aplicar a 'modificação' no shader:
        //Considerar a figura do 'Sully.png' que tem 4x4 imagens de movimentos (= 16 movimentos) array[4,4]
        //pathNome =./recursos/texturas/sully.png | nrChannels =4 | width =256 | height =256
        //se width(largura) = 256 ==> e são 4 imagens na coordenada X, então ==> 256/4 = 64pixels por imagem no eixo X
        //se width(largura) = 256 ==> e são 4 imagens na coordenada Y, então ==> 256/4 = 64pixels por imagem no eixo Y
        //Vou mostrar a figura da coordenada 0,0:
        meuShader1.use(); // O 'uso' do shader deve ser 'invocado' antes de iniciar as transformações -- senão o 'transform' não chegará no shader e será computado como '0' o que faz com que o personagem não apareça !
        glm::mat4 transform1 = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        transform1 = glm::scale(transform1, glm::vec3(0.3, 0.3, 0.0)); //
        //transform1 = glm::rotate(transform1, glm::radians(180.0f), glm::vec3(0.0, 0.0, 1.0)); // Tá de cabeça para baixo a imagem -- deixa de cabeça para cima
        transform1 = glm::translate(transform1, glm::vec3(pos_x_val, pos_y_val, 0.0f));
        unsigned int transformLoc1 = glGetUniformLocation(meuShader1.ID, "transform");
        glUniformMatrix4fv(transformLoc1, 1, GL_FALSE, glm::value_ptr(transform1));

        glUniform1i(glGetUniformLocation(meuShader1.ID, "sprite"), sprite_val); //
        unsigned int offsetx = glGetUniformLocation(meuShader1.ID, "offsetx");
        //void glUniform1f( 	GLint location,	GLfloat v0);
        //glUniform1f(transformAlfa0, 1.0);
        glUniform1f(offsetx, offsetx_val);
        unsigned int offsety = glGetUniformLocation(meuShader1.ID, "offsety");
        glUniform1f(offsety, offsety_val);

        //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


        // Troca de buffers e checagem/chamada de eventos:
        glfwSwapBuffers(window); // Troca os buffers de cor -- evitar o flickering
        glfwPollEvents(); // Checa se algum evento foi disparado -- limpa os eventos já ocorridos e processados ?
    }

    glfwTerminate(); // Deleta todos os recursos que o GLFW alocou
    return 0;
}
