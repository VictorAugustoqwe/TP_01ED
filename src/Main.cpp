#include "celulaStr.h"
#include "filaEncadeada.h"
#include <string>

using namespace std;

//Adiciona um dado na ultima posição do buffer do servidor desejado.
void info(string dado, int servidor, FilaEncadeada *servidores){
    servidores[servidor].enfileira(dado);
}

//Avanca o dado que esta na posicao desejada para a primeira posição do buffer (fura a fila).
void warn(int servidor, int posicao, FilaEncadeada *servidores){
    servidores[servidor].avancaFila(posicao);
}

//Transfere os dados do servidor um para o servidor dois na ordem que foram inseridos.
void tran(int servidor1, int servidor2, FilaEncadeada *servidores){
    string dado;
    while(!servidores[servidor1].vazio()){
        dado = servidores[servidor1].desenfilera();
        servidores[servidor2].enfileira(dado);
    }
}

//Imprime em qual servidor o erro ocorreu, e esvazia e imprime seus dados na política FIFO.
void erro(int servidor, FilaEncadeada *servidores){
    string dado;
    cout << "ERRO " << servidor << endl;
    while(!servidores[servidor].vazio()){
        dado = servidores[servidor].desenfilera();
        cout << dado << endl;
    }
}

//Envia o dado da primeira posição de cada buffer em servidores, imprimindo-os e retirando-os na política FIFO.
void send(FilaEncadeada *servidores, int nservidores, FilaEncadeada *historico){
    string dado;
    for(int servAtual = 0; servAtual < nservidores; servAtual++){
        if(!servidores[servAtual].vazio()){
            dado = servidores[servAtual].desenfilera();
            historico->enfileira(dado);
        }
    }
}

//Esvazia o histórico, imprimindo ele na política FIFO e esvazia todos os servidores imprimindo nessa mesma política.
void flush(FilaEncadeada *servidores, int nservidores, FilaEncadeada *historico){
    string dado;

    while(!historico->vazio()){
        dado = historico->desenfilera();
        cout << dado << endl;
    }
    for(int servAtual = 0; servAtual < nservidores; servAtual++){
        while(!servidores[servAtual].vazio()){
            dado = servidores[servAtual].desenfilera();
            cout << dado << endl;
        }
    }

}

/*
Interpreta a linha que foi lida do arquivo e executa o comando desejado já passando os parâmetros
que serão usados por ele.
*/
void interpretarComando(string linha, FilaEncadeada *servidores, int nservidores, FilaEncadeada *historico){
    int argnum = 0;
    int pos[5];

    string command;
    int serv, param;
    string dados;
    
    if(linha.length() > 3){
        for(unsigned int i = 0; i < linha.length(); i++){
            if(linha[i] == ' ' || linha[i] == '\n' || linha[i] == '\r'){
                pos[argnum] = i;
                argnum++;
            }
        }
    };
    command = linha.substr(0, pos[0]);
    if(command == "INFO"){
        serv = stoi(linha.substr(pos[0] + 1, pos[1] - pos[0] - 1));
        
        argnum = 0;
        for(unsigned int i = 0; i < linha.length(); i++){
            if(linha[i] == '"'){
                pos[argnum] = i;
                argnum++;
            }
        }

        dados = linha.substr(pos[0] + 1, pos[1] - pos[0] - 1);
        info(dados, serv, servidores);
    }
    else if(command == "WARN"){
        serv = stoi(linha.substr(pos[0] + 1, pos[1] - pos[0] - 1));
        param = stoi(linha.substr(pos[1] + 1, pos[2] - pos[1] - 1));
        warn(serv, param, servidores);
    }
    else if(command == "TRAN"){
        serv = stoi(linha.substr(pos[0] + 1, pos[1] - pos[0] - 1));
        param = stoi(linha.substr(pos[1] + 1, pos[2] - pos[1] - 1));
        tran(serv, param, servidores);
    }
    else if(command == "ERRO"){
        serv = stoi(linha.substr(pos[0] + 1, pos[1] - pos[0] - 1));
        erro(serv, servidores);
    }
    else if(command == "SEND"){
        send(servidores, nservidores, historico);
    }
    else if(command == "FLUSH"){
        flush(servidores, nservidores, historico);
    }

}

/*
Recebe o parâmetro que contém o arquivo que será aberto e lê arquivo linha a linha
chamando a função interpretarComando.
*/
int main(int argc, char* argv[]){
    try{
        int nservidores;
        char linha[100];
        FilaEncadeada *servidores;
        FilaEncadeada historico;
        
        FILE *file;
        file = fopen (argv[1],"r");

        if(!file)
            throw "Arquivo nao encontrado!";
        fscanf(file, "%d", &nservidores);

        servidores = new FilaEncadeada[nservidores];


        while (fgets(linha, 100, file)){
            string linhaString(linha);
            interpretarComando(linhaString, servidores, nservidores, &historico);
        }
        fclose(file);


        delete[] servidores;
    }
    catch(const char* e){
        cerr << e;
        return 1;
    }

    return 0;
}