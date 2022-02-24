#ifndef CELULA_H
#define CELULA_H

#include <iostream>

class celulaStr{
    public:
        //Construtor sem parâmetro.
        celulaStr();
        //Construtor que inicia o dado com o passado como parâmetro.
        celulaStr(std::string dado);
        //Recupera o dado da célula.
        std::string getDado() const;
        //Define o dado da célula.
        void setDado(std::string dado);
        //Recupera a próxima célula da fila. 
        celulaStr* getProximo() const;
        //Define a próxima célula da fila.
        void setProximo(celulaStr* ptr);
        //dado da célula atual
        std::string _nome;
        //endereço da próxima célula
        int dado;
};

#endif