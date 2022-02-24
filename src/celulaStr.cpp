#include "celulaStr.h"

//Construtor sem parâmetro.
celulaStr::celulaStr(){}

//Construtor que inicia o dado com o passado como parâmetro.
celulaStr::celulaStr(std::string dado): _dado(dado){}

//Recupera o dado da célula.
std::string celulaStr::getDado() const{
    return _dado;
}

//Define o dado da célula.
void celulaStr::setDado(std::string dado){
    _dado = dado;
}

//Recupera a próxima célula da fila.
celulaStr* celulaStr::getProximo() const{
    return _proximo;
}

//Define a próxima célula da fila.
void celulaStr::setProximo(celulaStr* proximo){
    _proximo = proximo;
}
