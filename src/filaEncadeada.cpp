#include "filaEncadeada.h"

//Construtor Padrão, inicia a fila.
FilaEncadeada::FilaEncadeada(){
    frente = new celulaStr;
    tras = frente;
}
//Destrutor padrão, desaloca toda a fila.
FilaEncadeada::~FilaEncadeada(){
    apaga();
    delete frente;
}

//Adiciona a célula com o dado passado como parâmetro no final da fila.
void FilaEncadeada::enfileira(std::string dado){
    celulaStr *novaCelula = new celulaStr(dado);
    tras->setProximo(novaCelula);
    tras = novaCelula;
    tamanho++;
}

//Retira e retorna o dado da célula na primeira posição da fila.
std::string FilaEncadeada::desenfilera(){
    celulaStr *apagada;
    std::string aux;

    if(tamanho == 0)
        throw "Fila esta vazia!";

    aux = frente->getProximo()->getDado();
    apagada = frente;
    frente = frente -> getProximo();
    delete apagada;
    tamanho--;
    return aux;
}

//Avança a célula na posição passada como parâmetro.
void FilaEncadeada::avancaFila(int posicao){
    celulaStr *percorre;
    celulaStr *aux;
    if(posicao > tamanho)
        throw "Fila não tem essa posição";
    percorre = frente;
    for(int repetir = 0; repetir < posicao; repetir++){
        percorre = percorre -> getProximo();
    }
    aux = percorre;
    percorre = percorre->getProximo();
    aux->setProximo(aux->getProximo()->getProximo());
    percorre->setProximo(frente->getProximo());
    frente->setProximo(percorre);
    
}

//Apaga todas as células da fila exceto a frente.
void FilaEncadeada::apaga(){
    while (tamanho > 0){
        desenfilera();        
    }   
}

//Retorna se a fila esta vazia.
bool FilaEncadeada::vazio() const{
    return (tamanho == 0);
}
