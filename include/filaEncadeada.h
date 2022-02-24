#ifndef FILAENCADEADA_H
#define FILAENCADEADA_H

#include "celulaStr.h"


class FilaEncadeada{
    public:
        //Construtor Padrão, inicia a fila.
        FilaEncadeada();
        //Destrutor padrão, desaloca toda a fila.
        ~FilaEncadeada();
        //Adiciona a célula com o dado passado como parâmetro no final da fila.
        void enfileira(std::string dado);
        //Retira e retorna o dado da célula na primeira posição da fila.
        std::string desenfilera();
        //Avança a célula na posição passada como parâmetro.
        void avancaFila(int posicao);
        //Apaga todas as células da fila exceto a frente.
        void apaga();
        //Retorna se a fila esta vazia.
        bool vazio() const;
        
    private:
        //Tamanho atual da fila.
        int tamanho = 0;
        //Aponta para a primeira célula da fila.
        celulaStr *frente = nullptr;
        //Aponta para a última célula da fila.
        celulaStr *tras = nullptr;
};

#endif