// UNISINOS
// Curso: Ciência da Computação - Híbrido
// Atividade Acadêmica - Processamento Gráfico
// Módulo 7
// Tarefa: Prova Grau B - Implementação de um jogo simples com Tilemap Isométrico
// Data: 11/07/2024
// Professor: Fernando Marson & Rossana Baptista Queiroz
// Alunos: Paulo Griebler Júnior & Rodrigo Ferreira Pires & Eduardo Colissi Wiceskoski
// Registros Acadêmicos: 1930669 & 1917485 & 192736

#include "Log.h"

Log* Log::instance = nullptr;

Log::Log() {
    impNoTerminal = true; // Ativa a impressão no terminal -- se não quiser saída de logs defina como false ou use 'naoImprimirNoTerminal()'

}

Log* Log::getInstance() {
    //cout << "Entrou em: Log* log::getInstance()" << endl; // Log

	if (instance == nullptr)
		{
		instance = new Log();
		}
	return instance;
};

void Log::naoImprimirNoTerminal(){
    impNoTerminal = false;
}

void Log::imprimirNoTerminal() {
    impNoTerminal = true;
}

void Log::log(string msg) {
    if (impNoTerminal) cout << "LOG: " << msg;
}

void Log::logN(string msg) {
    if (impNoTerminal) {
        msg += "\n";
        log(msg);
    }
}

void Log::funcao(string msg) {
    if (impNoTerminal) cout << "LOG: - Entrou na função: " << msg;
}

void Log::funcaoN(string msg) {
    if (impNoTerminal) {
        msg += "\n";
        funcao(msg);
    }
}

void Log::deb(string msg) {
    if (impNoTerminal) cout << "DEB: " << msg;
}

void Log::debN(string msg) {
    if (impNoTerminal) {
        msg += "\n";
        deb(msg);
    }
}

void Log::aviso(string msg) {
    if (impNoTerminal) cout << "# AVISO: " << msg;
}

void Log::avisoN(string msg) {
    if (impNoTerminal) {
        msg += "\n";
        aviso(msg);
    }
}

void Log::erro(string msg) {
     if (impNoTerminal) cout << "### ERRO: " << msg;
}

void Log::erroN(string msg) {
    if (impNoTerminal) {
        msg += "\n";
        erro(msg);
    }
}
