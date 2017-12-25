//  A classe Mesa possui como atributos:
//      Um mutex que é compartilhado entre todas as threads;
//      Um objeto da classe Tabaqueiro;
//      Uma variável de condição que é compartilhada entre todos os fumantes;
//      Um vetor de fumantes;
//      Um vetor de threads;
//      Um vetor que armazena se a mesa possui determinado ingrediente.
//
//  Além disso, possui um construtor e o método Iniciar().

#ifndef MESA_H_INCLUDED
#define MESA_H_INCLUDED
#include <mutex>
#include <thread>
#include "Tabaqueiro.h"

class Mesa{

private:
    mutex* mtx;
    Tabaqueiro tabaqueiro;
    condition_variable podeFumar;
    Fumante* fumante;
    thread* execucao;
    int* produto;

public:
    Mesa();
    void Iniciar();
};

//O construtor da mesa não recebe parâmetros, contudo, ele precisa alocar memória para todos os atributos de classe, além disso, cria as threads.
Mesa::Mesa(){
    //Aloca memória para os atributos.
    fumante = new Fumante[3];
    execucao = new thread[4];
    produto = new int[3];
    mtx = new mutex();

    //Limpa os valores do vetor de produtos e constrói os fumantes com a referência da variável de condição que os controlará.
    for(int i = 0; i < 3; i++){
        produto[i] = 0;
        fumante[i] = (&podeFumar);
    }

    //Cria as threads.
    execucao[0] = thread(&Fumante::Enrolar, &fumante[0], mtx, tabaqueiro.getCondition(), produto, 0);
    execucao[1] = thread(&Fumante::Enrolar, &fumante[1], mtx, tabaqueiro.getCondition(), produto, 1);
    execucao[2] = thread(&Fumante::Enrolar, &fumante[2], mtx, tabaqueiro.getCondition(), produto, 2);
    execucao[3] = thread(&Tabaqueiro::FornecerProdutos, &tabaqueiro, mtx, &podeFumar, produto);

    //Dá a notificação para o tabaqueiro começar.
    tabaqueiro.getCondition()->notify_one();
}

//O método Iniciar() não recebe parâmetros e a sua única função é sincronizar as threads.
void Mesa::Iniciar(){
    for(int i = 0; i < 4; i++){
        execucao[i].join();
    }
}

#endif
