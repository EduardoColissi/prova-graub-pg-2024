// UNISINOS
// Curso: Ciência da Computação - Híbrido
// Atividade Acadêmica - Processamento Gráfico
// Módulo 7
// Tarefa: Teste de Losango
// Data: 12/07/2024
// Professora: Rossana Baptista Queiroz
// Aluno: Paulo Griebler Júnior
// Registro Acadêmico: 1930669

// Objetivo: Desenvolver o menor código possível que permita detectar cliques de mouse dentro do losango 100x60

//Compilar com: g++ prova.cpp -o prova Log.cpp Tile.cpp Losango.cpp Map.cpp src/glad.c -I include -L/usr/lib/x86_64-linux-gnu/ -L/usr/lib64 -lGLEW -lGL -lX11 -lglfw -lrt -lm -ldl
// Rodar com: ./prova



#include <glad/glad.h> // É necessário que a inclusão do glad.h seja feita antes da inclusão do glfw3 -- aliás o glad.h precisa ser incluído ANTES de qualquer outro arquivo cabeçalho que use os arquivos cabeçalhos do OpenGL (tipo GL/gl.h)
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp> // Para imprimir um vetor de glm... bem útil...

#include <iostream>
#include "Shader.h"

#include "Map.h" // Necessário que este include esteja antes de #include "stb_image.h" abaixo

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h" // github.com/nothings/stb/blob/master/stb_image.h

using namespace std;

// Variáveis globais que organizam movimento do personagem:
int scale_val = 1; //
const int SCALE_VAL_MIN = 0;
const int SCALE_VAL_MAX = 10;

float offsetx_val = 0.0; // Deslocamento da sprite no eixo X -- Varia de 0
const float OFFSETX_VAL_MIN = 0.0;
const float OFFSETX_VAL_MAX = 1.0;
float offsety_val = 0.0; // Deslocamento da sprite no eixo Y
const float OFFSETY_VAL_MIN = 0.0;
const float OFFSETY_VAL_MAX = 1.0;

const float OFFSETDELTA = 0.33; // Porque tem 3 imagens em uma linha ou coluna (9x9)
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


    if(glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) { // Deve REDUZIR o scale da scale do personagem
        if(scale_val <= SCALE_VAL_MIN) { // Verifica se já não está no valor mínimo
            cout << "###AVISO: 'scale_val' já está no valor mínimo que é: " << SCALE_VAL_MIN << endl;
        }
        else {
            scale_val--;
            cout << "'scale_val' =" << scale_val << endl;
        }
    }
    if(glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) { // Deve AUMENTAR o scale da scale do personagem
        if(scale_val >= SCALE_VAL_MAX) { // Verifica se já não está no valor máximo
            cout << "###AVISO: 'scale_val' já está no valor máximo que é: " << SCALE_VAL_MAX << endl;
        }
        else {
            scale_val++;
            cout << "'scale_val' =" << scale_val << endl;
        }
    }

    if(glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS) { // Deve REDUZIR o offset do personagem
        if(offsetx_val <= OFFSETX_VAL_MIN) { // Verifica se já não está no valor mínimo
            cout << "###AVISO: 'offsetx_val' já está no valor mínimo que é: " << OFFSETX_VAL_MIN << endl;
        }
        else {
            offsetx_val -= OFFSETDELTA;
            cout << "'offsetx_val' =" << offsetx_val << endl;
        }
    }
    if(glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS) { // Deve AUMENTAR o offset do personagem
        if(offsetx_val >= OFFSETX_VAL_MAX) { // Verifica se já não está no valor máximo
            cout << "###AVISO: 'offsetx_val' já está no valor máximo que é: " << OFFSETX_VAL_MAX << endl;
        }
        else {
            offsetx_val += OFFSETDELTA;
            cout << "'offsetx_val' =" << offsetx_val << endl;
        }
    }

    if(glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS) { // Deve REDUZIR o offset do personagem
        if(offsety_val <= OFFSETY_VAL_MIN) { // Verifica se já não está no valor mínimo
            cout << "###AVISO: 'offsety_val' já está no valor mínimo que é: " << OFFSETY_VAL_MIN << endl;
        }
        else {
            offsety_val -= OFFSETDELTA;
            cout << "'offsety_val' =" << offsety_val << endl;
        }
    }
    if(glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS) { // Deve AUMENTAR o offset do personagem
        if(offsety_val >= OFFSETY_VAL_MAX) { // Verifica se já não está no valor máximo
            cout << "###AVISO: 'offsety_val' já está no valor máximo que é: " << OFFSETY_VAL_MAX << endl;
        }
        else {
            offsety_val += OFFSETDELTA;
            cout << "'offsety_val' =" << offsety_val << endl;
        }
    }

    // Muda a posição do personagem:
    if(glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) { // Deve REDUZIR o valor do pos_x_val -- Deve movimentar o personagem para ESQ.
        if(pos_x_val <= POS_X_VAL_MIN) {
            cout << "###AVISO: 'pos_x_val' já está no valor mínimo que é: " << POS_X_VAL_MIN << endl;
        }
        else {
            pos_x_val -= 0.005;
            cout << "'pos_x_val' =" << pos_x_val << endl;
        }
    }
    if(glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) { // Deve AUMENTAR o valor do pos_x_val
        if(pos_x_val >= POS_X_VAL_MAX) {
            cout << "###AVISO: 'pos_x_val' já está no valor mínimo que é: " << POS_X_VAL_MAX << endl;
        }
        else {
            pos_x_val += 0.005;
            cout << "'pos_x_val' =" << pos_x_val << endl;
        }
    }

    // Muda o offsety do personagem:
    if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) { // Deve REDUZIR o valor do pos_y_val
        if(pos_y_val <= POS_Y_VAL_MIN) {
            cout << "###AVISO: 'pos_y_val' já está no valor mínimo que é: " << POS_Y_VAL_MIN << endl;
        }
        else {
            pos_y_val -= 0.005;
            cout << "'pos_y_val' =" << pos_y_val << endl;
        }

    }
    if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) { // Deve AUMENTAR o valor do pos_y_val
        if(pos_y_val >= POS_Y_VAL_MAX) {
            cout << "###AVISO: 'pos_y_val' já está no valor mínimo que é: " << POS_Y_VAL_MAX << endl;
        }
        else {
            pos_y_val += 0.005;
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

    GLFWwindow* window = glfwCreateWindow(800, 600, "M7 - Teste de Coordenadas Ortográficas", NULL, NULL);
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
    Shader shaderLos("./los_vs.glsl", "./los_fs.glsl"); // Shader para a Los

    float widthProj = 800.0;
    float heightProj = 600.0;
    float widthObj = 100.0; //400.0; //100.0;
    float heightObj = 60.0;

    //static pair<Triangulo, Triangulo>obterPontosDoLosangoParaCalculoDeVertices(float widthProj, float heightProj, float widthObj, float heightObj);
    pair<Triangulo, Triangulo> par = Losango::obterPontosDoLosangoParaCalculoDeVertices( widthProj, heightProj, widthObj, heightObj);

    Vertice A = par.first.a;
    float Ax = A.x;
    float Ay = A.y;
    Vertice B = par.first.b;
    float Bx = B.x;
    float By = B.y;
    Vertice C = par.first.c;
    float Cx = C.x;
    float Cy = C.y;
    Vertice D = par.second.a;
    float Dx = D.x;
    float Dy = D.y;
    Vertice E = par.second.b;
    float Ex = E.x;
    float Ey = E.y;
    Vertice F = par.second.c;
    float Fx = F.x;
    float Fy = F.y;

    float vertices_LOS[] = {
        //X  Y    Z      R    G    B
        // T0
        Ax, Ay,  0.0,   1.0, 1.0, 0.0, // A
        Bx, By,  0.0,   1.0, 1.0, 0.0, // B
        Cx, Cy,  0.0,   1.0, 1.0, 0.0, // C
        // T1
        Dx, Dy,  0.0,   1.0, 1.0, 0.0, // D
        Ex, Ey,  0.0,   1.0, 1.0, 0.0, // E
        Fx, Fy,  0.0,   1.0, 1.0, 0.0 // F
    };

    unsigned int VBO_LOS, VAO_LOS;
    glGenVertexArrays(1, &VAO_LOS);
    glGenBuffers(1, &VBO_LOS);

    glBindVertexArray(VAO_LOS);

    glBindBuffer(GL_ARRAY_BUFFER, VBO_LOS);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_LOS), vertices_LOS, GL_STATIC_DRAW);

    // position attribute
    //void glVertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void * pointer);
    // index = ordem no array de informações (0 para vértices/1 para texturas)
    // size = tamanho da informação (para vértices = 3 / para texturas = 2)
    // stride = deslocamento entre este byte de informação (vértice ou textura) em relação ao próximo byte de informação de (vertice ou textura)
    // pointer = deslocamento entre as colunas de bytes de informação (vertice = 0/textura = 3*sizeof(float)) // Sempre: X*sizeof(tipo_em_uso)
    // Um float em C++ ocupa 4 bytes = 32 bits // Double ocupa 8 bytes (64 bits) ?
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    /*// color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);*/ // Não tem cor aqui, só textura !
    // texture coord attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);





    // Mostra a mensagem de início -- teclas, funcionamento...
    mensagem_de_inicio();


    Map map = Map();
    vector<Tile> vecTiles = map.getVecTiles();
    //Tile(string nome, float offsetX, float offsetY, bool caminhavel, bool fatal);
    //vecTiles.push_back(Tile("pedra",        0.33, 0.66, true, false)); // 8
    Tile tile = vecTiles.at(8);
    //Losango(float x, float y, float w, float h, float tX, float tY, Tile tile, bool ativo);
    Losango losango = Losango(5, 5, 100, 60, 100, 100, tile, true);


    tempo_anterior = glfwGetTime();
    cout << "tempo_anterior =" << tempo_anterior << endl;


    glEnable(GL_BLEND); // Permitem que a camada transparente do canal alfa de um PNG possa realmente ser 'transparente' ao encontrar se sobrepor à outras camadas de outras sprites que não são transparentes
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Loop de renderização
    while(!glfwWindowShouldClose(window)) { // Loop que mantém o desenho da janela principal --> Se glfwWindowShouldClose(window) retorna 'true' o loop pára e o programa encerra


        // Entradas:
        tempo_atual = glfwGetTime();
        //cout << "tempo_atual =" << tempo_atual << endl;
        //tempo_anterior =0.326702
        //tempo_atual =0.326723
        //tempo_atual =0.327641
        //cout << "tempo_atual - tempo_anterior =" << (tempo_atual - tempo_anterior) << endl;
        if ((tempo_atual - tempo_anterior) > 0.1) { // Avalia o tempo decorrido para autorizar o processo de inputs (e mudar as sprites do personagem)
            //processInput(window); // Processa os eventos ocorridos
            tempo_anterior = tempo_atual;
        }

        const int state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
        if (state == GLFW_PRESS) {
            double mx, my;
            glfwGetCursorPos(window, &mx, &my);
            cout << "Posição do mouse: mx=" << mx << "| my=" << my << endl;
            //static void seEstaDentroDoLosangoradoDesativa_o(Losango& losango[10][10], int mx, int my)
            //Losango::seEstaDentroDoLosangoradoDesativa_o(losango, mx, my);
            bool colidiu = Losango::estaDentroDoLosango(losango, mx, my);
            cout << "colidiu =" << colidiu << endl;
        }



        // Comandos de renderização:
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        //glClear(GL_COLOR_BUFFER_BIT); // Aplica as cores acima ao buffer de cor -- poderia aplicar as cores acima a outros buffers (GL_DEPTH_BUFFER_BIT OU GL_STENCIL_BUFFER_BIT)
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Usa GL_DEPTH_BUFFER_BIT para apagar o buffer das texturas


        // Desenha a grid:
        shaderLos.use(); // O 'uso' do shader deve ser 'invocado' antes de iniciar as transformações -- senão o 'transform' não chegará no shader e será computado como '0' o que faz com que o personagem não apareça ! -- Shader antes de glBindVertexArray...
        glBindVertexArray(VAO_LOS);

        glm::mat4 projection = glm::ortho(0.0, 800.0, 0.0, 600.0, -1.0, 1.0); // Isto vai ser enviado para o shader para que o mesmo trabalhe com coordenados ortográficas -- USAR SEMPRE ESTE TIPO DE COORDENADA PQ AS CLASSES FORAM CONSTRUÍDAS CONSIDERANDO QUE O EIXO Y CRESCE PARA CIMA !
        //glm::mat4 proj = glm::ortho(0.0f, (float)WIDTH, (float)HEIGHT, 0.0f, -1.0f, 1.0f); // Retirado do exemplo_04.cpp linha 155
        //glm::mat4 projection = glm::ortho(0.0, 800.0, 600.0, 0.0, -1.0, 1.0); // Aqui se usaria (NÃO USE !) se quisesse que o eixo Y crescesse para baixo

        //cout << "glm::to_string(projection) =" << glm::to_string(projection) << endl;

        unsigned int projectionLoc = glGetUniformLocation(shaderLos.ID, "projection");
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
        glm::mat4 transform1 = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first

        transform1 = glm::scale(transform1, glm::vec3(losango.getSX(), losango.getSY(), 0.0)); // CUIDADO ao usar scale com a projeção pq sem scale o objeto vai ficar do tamanho de um ponto e se usar uma escala menor que 1 vai ficar menor ainda... Confirmado.. 0.3 em scale fez o objeto desaparecer !!!
        transform1 = glm::translate(transform1, glm::vec3(losango.getX(), losango.getY(), 0.0)); // Tem que ter um 'translate' no uso da 'projection' senão o objeto fica na região esq./inf. da tela (quase imperceptível)


        unsigned int transformLoc1 = glGetUniformLocation(shaderLos.ID, "transform");
        glUniformMatrix4fv(transformLoc1, 1, GL_FALSE, glm::value_ptr(transform1));

        //glUniform1i(glGetUniformLocation(meuShader1.ID, "sprite"), sprite_val); //
        //unsigned int offsetx = glGetUniformLocation(meuShader1.ID, "offsetx");
        //void glUniform1f( 	GLint location,	GLfloat v0);
        //glUniform1f(transformAlfa0, 1.0);
        //glUniform1f(offsetx, offsetx_val);
        //unsigned int offsety = glGetUniformLocation(meuShader1.ID, "offsety");
        //glUniform1f(offsety, offsety_val);
        //glDrawElements(GL_LINES, 2, GL_UNSIGNED_INT, 0); // Como não usou EBO não pode chamar essa função -- MUITO CUIDADO AQUI !! // Thread 1 "coordenadas_ort" received signal SIGSEGV, Segmentation fault. __memcpy_avx_unaligned_erms ()
        //https://www.khronos.org/opengl/wiki/Primitive
        //There are 3 kinds of line primitives, based on different interpretations of a vertex stream.
        //GL_LINES: Vertices 0 and 1 are considered a line. Vertices 2 and 3 are considered a line. And so on. If the user specifies a non-even number of vertices, then the extra vertex is ignored.
        //GL_LINE_STRIP: The adjacent vertices are considered lines. Thus, if you pass n vertices, you will get n-1 lines. If the user only specifies 1 vertex, the drawing command is ignored.
        //GL_LINE_LOOP: As line strips, except that the first and last vertices are also used as a line. Thus, you get n lines for n input vertices. If the user only specifies 1 vertex, the drawing command is ignored. The line between the first and last vertices happens after all of the previous lines in the sequence.
        //glDrawArrays(GL_LINES, 0, 4);
        glDrawArrays(GL_LINE_LOOP, 0, 6);
        //glDrawArrays(GL_TRIANGLES, 0, 6); // OK -- Funciona !


        // Troca de buffers e checagem/chamada de eventos:
        glfwSwapBuffers(window); // Troca os buffers de cor -- evitar o flickering
        glfwPollEvents(); // Checa se algum evento foi disparado -- limpa os eventos já ocorridos e processados ?
    }

    glfwTerminate(); // Deleta todos os recursos que o GLFW alocou
    return 0;
}
