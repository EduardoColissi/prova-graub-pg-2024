// UNISINOS
// Curso: Ciência da Computação - Híbrido
// Atividade Acadêmica - Processamento Gráfico
// Módulo 7
// Tarefa: Prova Grau B - Implementação de um jogo simples com Tilemap Isométrico
// Data: 11/07/2024
// Professor: Fernando Marson & Rossana Baptista Queiroz
// Alunos: Paulo Griebler Júnior & Rodrigo Ferreira Pires & Eduardo Colissi Wiceskoski
// Registros Acadêmicos: 1930669 & 1917485 & 192736

// Objetivo: Todos os logs devem ser feitos pelos métodos desta classe

#ifndef LOG_H
#define LOG_H

#include<iostream>
#include<string>

using namespace std;

class Log {
    private:
        static Log* instance;
        //https://www.tabnews.com.br/brunohfdev/duvida-entre-os-termos-terminal-console-e-shell
        bool impNoTerminal; // Usando o termo 'terminal' em vez de 'console'

        Log (); // Construtor privado - padrão Singleton
        ~Log();

    public:
        static Log* getInstance();

        void naoImprimirNoTerminal();
        void imprimirNoTerminal();

        void log(string msg);
        void logN(string msg);
        void funcao(string msg);
        void funcaoN(string msg);
        void deb(string msg);
        void debN(string msg);
        void aviso(string msg);
        void avisoN(string msg);
        void erro(string msg);
        void erroN(string msg);

};

#endif


