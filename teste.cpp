// UNISINOS
// Curso: Ciência da Computação - Híbrido
// Atividade Acadêmica - Processamento Gráfico
// Módulo 7
// Tarefa: Prova Grau B - Implementação de um jogo simples com Tilemap Isométrico
// Data: 03/07/2024
// Professor: Fernando Marson & Rossana Baptista Queiroz
// Alunos: Paulo Griebler Júnior & Rodrigo Ferreira Pires & Eduardo Colissi Wiceskoski
// Registros Acadêmicos: 1930669 & 1917485 & 192736


//Compilar com: g++ teste.cpp -o teste Config.cpp Tile.cpp Quad.cpp Map.cpp src/glad.c -I include -L/usr/lib/x86_64-linux-gnu/ -L/usr/lib64 -lGLEW -lGL -lX11 -lglfw -lrt -lm -ldl
// Rodar com: ./teste

/*#include <glad/glad.h> // É necessário que a inclusão do glad.h seja feita antes da inclusão do glfw3 -- aliás o glad.h precisa ser incluído ANTES de qualquer outro arquivo cabeçalho que use os arquivos cabeçalhos do OpenGL (tipo GL/gl.h)
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <cmath> // para sin()
//#include <filesystem>

#include "Shader.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h" // github.com/nothings/stb/blob/master/stb_image.h*/ // DEL


#include "Map.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h" // github.com/nothings/stb/blob/master/stb_image.h

using namespace std;

int main() {

    //Config config = Config::getInstance(); // error: use of deleted function ‘Config::Config(const Config&)’

    //Singleton* singleton = Singleton::GetInstance("FOO");
    Config* config = Config::getInstance();

    // Instancia um objeto da classe Quad:
    //Quad(int x, int y, int w, int h, float tX, float tY, Tile tile, bool ativo, bool caminhavel, bool fatal);
    //Quad quad = Quad();

    Map map = Map();
    vector<Tile> vecTiles = map.getVecTiles();

    for (int i = 0; i < vecTiles.size(); i++) {
        cout << "vecTiles.at(" << i << ").toString(): " << vecTiles.at(i).toString() << endl;
    }

    //void Map::carregarMapa(string arquivo)
    map.carregarMapa("mapa.txt");

    map.MostraMapaNaTela();



















    //mensagem_de_inicio();

    //double glfwGetTime(void) This function returns the value of the GLFW timer. Unless the timer has been set using glfwSetTime, the timer measures time elapsed since GLFW was initialized.
    //Returns  The current value, in seconds, or zero if an error occurred.
    //Remarks  This function may be called from secondary threads.
    //Note  The resolution of the timer is system dependent, but is usually on the order of a few micro- or nanoseconds. It uses the highest-resolution monotonic time source on each supported platform.


    config->setTempoAnterior(glfwGetTime());
    cout << "config->getTempoAnterior() =" << config->getTempoAnterior() << endl;


    glEnable(GL_BLEND); // Permitem que a camada transparente do canal alfa de um PNG possa realmente ser 'transparente' ao encontrar se sobrepor à outras camadas de outras sprites que não são transparentes
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    // Loop de renderização
    while(!glfwWindowShouldClose(config->getWindow())) { // Loop que mantém o desenho da janela principal --> Se glfwWindowShouldClose(window) retorna 'true' o loop pára e o programa encerra
        glm::mat4 projection = glm::ortho(0.0, 800.0, 0.0, 600.0, -1.0, 1.0);

        // Entradas:
        config->setTempoAtual(glfwGetTime());
        //cout << "tempo_atual =" << tempo_atual << endl;
        //tempo_anterior =0.326702
        //tempo_atual =0.326723
        //tempo_atual =0.327641
        //cout << "tempo_atual - tempo_anterior =" << (tempo_atual - tempo_anterior) << endl;
        if ((config->getTempoAtual() - config->getTempoAnterior()) > 0.5) { // Avalia o tempo decorrido para autorizar o processo de inputs (e mudar as sprites do personagem)
            //processInput(window); // Processa os eventos ocorridos
            config->setTempoAnterior(config->getTempoAtual());
        }



        // Comandos de renderização:
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        //glClear(GL_COLOR_BUFFER_BIT); // Aplica as cores acima ao buffer de cor -- poderia aplicar as cores acima a outros buffers (GL_DEPTH_BUFFER_BIT OU GL_STENCIL_BUFFER_BIT)
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Usa GL_DEPTH_BUFFER_BIT para apagar o buffer das texturas


        // Desenha o mapa isométrico:
        //glBindVertexArray(config->getVAO());
        glBindVertexArray(0);
        glBindTexture(GL_TEXTURE_2D, config->texture[0]); // Ativa a textura do fundo
        glm::mat4 transform0 = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        // Não aplica nenhuma outra transformação aqui pois esse é o fundo...
        //transform0 = glm::rotate(transform0, glm::radians(180.0f), glm::vec3(0.0, 0.0, 1.0)); // Tá de cabeça para baixo a imagem -- deixa de cabeça para cima ==> resolvido na inversão da coordenada T(Y) em vertices[]
        transform0 = glm::scale(transform0, glm::vec3(1.0, 1.0, 0.0));
        config->getShader().use();
        unsigned int transformLoc0 = glGetUniformLocation(config->getShader().ID, "transform");
        //glUniformMatrix4fv(transformLoc0, 1, GL_FALSE, glm::value_ptr(transform0));
        //unsigned int transformAlfa0 = glGetUniformLocation(meuShader0.ID, "canalAlfa");
        //void glUniform1f( 	GLint location,	GLfloat v0);
        //glUniform1f(transformAlfa0, 1.0); // 1.0 - Canal Alfa totalmente ativo !!!
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // Mostra só as linhas (contornos) dos 2 triângulos -- deu para ver que 1° desenha os triângulos preenchidos e depois desenha de novo só com o contorno

        // Desenha o personagem:
        //glBindVertexArray(VAO_PER);
        //glBindTexture(GL_TEXTURE_2D, texture[1]); // Ativa a textura do fundo
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
        /*meuShader1.use(); // O 'uso' do shader deve ser 'invocado' antes de iniciar as transformações -- senão o 'transform' não chegará no shader e será computado como '0' o que faz com que o personagem não apareça !
        glm::mat4 transform1 = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        transform1 = glm::scale(transform1, glm::vec3(0.3, 0.3, 0.0)); //
        transform1 = glm::rotate(transform1, glm::radians(180.0f), glm::vec3(0.0, 0.0, 1.0)); // Tá de cabeça para baixo a imagem -- deixa de cabeça para cima
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

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);*/


        // Troca de buffers e checagem/chamada de eventos:
        glfwSwapBuffers(config->getWindow()); // Troca os buffers de cor -- evitar o flickering
        glfwPollEvents(); // Checa se algum evento foi disparado -- limpa os eventos já ocorridos e processados ?
    }

    glfwTerminate(); // Deleta todos os recursos que o GLFW alocou
    return 0;


}
