// UNISINOS
// Curso: Ciência da Computação - Híbrido
// Atividade Acadêmica - Processamento Gráfico
// Módulo 7
// Tarefa: Prova Grau B - Implementação de um jogo simples com Tilemap Isométrico
// Data: 03/07/2024
// Professor: Fernando Marson & Rossana Baptista Queiroz
// Alunos: Paulo Griebler Júnior & Rodrigo Ferreira Pires & Eduardo Colissi Wiceskoski
// Registros Acadêmicos: 1930669 & 1917485 & 1927367

#include "Persona.h"

Persona::Persona(GLFWwindow* window) {
    init();
    log->funcaoN("Persona::Persona(GLFWwindow* window)");

    this->window = window;
    this->x = 0;
    this->y = 0;
    this->w = 0.0;
    this->h = 0.0;
    this->sX = 0.0;
    this->sY = 0.0;
    this->offsetX = 0.0;
    this->offsetY = 0.0;
    this->ativo = false;



};

Persona::Persona(GLFWwindow* window, int x, int y, float w, float h, float sX, float sY, float offsetX, float offsetY, bool ativo) {
    init();
    log->funcaoN("Persona::Persona(GLFWwindow* window, float "+to_string(x)+", float "+to_string(y)+", float "+to_string(w)+", float "+to_string(h)+", float "+to_string(sX)+", float "+to_string(sY)+", bool "+to_string(ativo)+")"); //error: invalid operands of types ‘const char [18]’ and ‘float’ to binary ‘operator+’

    this->window = window;
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
    this->sX = sX;
    this->sY = sY;
    this->offsetX = 0.0;
    this->offsetY = 0.0;
    this->ativo = ativo;


};

// Usado por todos os construtores
void Persona::init() {
    log = Log::getInstance();
    log->funcaoN("void Persona::init()");

};



Persona::~Persona() {
};



int Persona::getX() {
    return x;
}

int Persona::getY() {
    return y;
}

float Persona::getW() {
    return w;
}

float Persona::getH() {
    return h;
}

float Persona::getSX() {
    return sX;
}

float Persona::getSY() {
    return sY;
}

float Persona::getOffsetX() {
    return offsetX;
}

float Persona::getOffsetY() {
    return offsetY;
}

void Persona::setAtivo(bool ativo) {
    this->ativo = ativo;
}

bool Persona::isAtivo() {
    return ativo;
}

// Muda a posição do personagem:
void Persona::movimento(Map* map) {

    vector<vector<Losango>> vecLosangos = map->getVecLosangos();

    if(glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {
        if(x <= 0) {
            cout << "###AVISO: 'x' já está no valor mínimo que é: " << 0 << endl;
        }
        else x--;
        if(y <= 0) {
            cout << "###AVISO: 'y' já está no valor mínimo que é: " << 0 << endl;
        }
        else y--;
    }

    if(glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS) { // Deve REDUZIR o valor do pos_x_val -- Deve movimentar o personagem para ESQ.
        if(x <= 0) {
            cout << "###AVISO: 'x' já está no valor mínimo que é: " << 0 << endl;
        }
        else x--;
    }

    if(glfwGetKey(window, GLFW_KEY_7) == GLFW_PRESS) {
        if(x <= 0) {
            cout << "###AVISO: 'x' já está no valor mínimo que é: " << 0 << endl;
        }
        else x--;
        if(y >= vecLosangos.size()) {
            cout << "###AVISO: 'y' já está no valor máximo que é: " << vecLosangos.at(0).size() << endl;
        }
        else y++;
    }

    if(glfwGetKey(window, GLFW_KEY_8) == GLFW_PRESS) { // Deve AUMENTAR o valor do pos_y_val
        if(y >= vecLosangos.size()) {
            cout << "###AVISO: 'y' já está no valor máximo que é: " << vecLosangos.at(0).size() << endl;
        }
        else {
            y++;
        }
    }

    if(glfwGetKey(window, GLFW_KEY_9) == GLFW_PRESS) {
        if(x >= vecLosangos.size()) {
            cout << "###AVISO: 'x' já está no valor máximo que é: " <<  vecLosangos.size()<< endl;
        }
        else x++;
        if(y >= vecLosangos.size()) {
            cout << "###AVISO: 'y' já está no valor máximo que é: " << vecLosangos.at(0).size() << endl;
        }
        else y++;
    }

    if(glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS) { // Deve AUMENTAR o valor do pos_x_val
        if(x >= vecLosangos.at(0).size()) {
            cout << "###AVISO: 'x' já está no valor máximo que é: " <<  vecLosangos.at(0).size() << endl;
        }
        else x++;
    }

    if(glfwGetKey(window, GLFW_KEY_9) == GLFW_PRESS) {
        if(x >= vecLosangos.size()) {
            cout << "###AVISO: 'x' já está no valor máximo que é: " <<  vecLosangos.size()<< endl;
        }
        else x++;
        if(y >= vecLosangos.size()) {
            cout << "###AVISO: 'y' já está no valor máximo que é: " << vecLosangos.at(0).size() << endl;
        }
        else y++;
    }

    if(glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) { // Deve REDUZIR o valor do pos_y_val
        if(y <= 0) {
            cout << "###AVISO: 'y' já está no valor mínimo que é: " << 0 << endl;
        }
        else y--;
    }

}

string Persona::toString() {
    string str = string("Persona: [x:");
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
    str += ", offsetX:";
    str += to_string(offsetX);
    str += ", offsetY:";
    str += to_string(offsetY);
    str += ", ativo:";
    str += to_string(ativo);
    str += "]";

    return str;

};



