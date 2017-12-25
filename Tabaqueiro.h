//  A classe Tabaqueiro possui como atributo somente a variável de condição que o controlará. Além disso, possui um construtor, um método para
//  adquirir a referência de sua variável de condição, e o método FornecerProdutos().

#ifndef TABAQUEIRO_H_INCLUDED
#define TABAQUEIRO_H_INCLUDED
#include <condition_variable>
#include <mutex>
#include <unistd.h>

using namespace std;

class Tabaqueiro{

private:
    condition_variable podeFornecer;

public:
    Tabaqueiro();
    condition_variable* getCondition();
    void FornecerProdutos(mutex* mtx, condition_variable* podeFumar, int produto[3]);
};

//Construtor padrão.
Tabaqueiro::Tabaqueiro(){
}

//getCondition() retorna a referência da variável de condição do tabaqueiro.
condition_variable* Tabaqueiro::getCondition(){
    return &podeFornecer;
}

//O método FornecerProdutos() recebe como parâmetros a referência do mutex que é compartilhado entre todas as threads, a referência da variável de
//condição que controla os fumantes e o vetor de produtos. Sua função é a de gerar índices aleatórios para o vetor de produtos.
void Tabaqueiro::FornecerProdutos(mutex* mtx, condition_variable* podeFumar, int produto[3]){
    int prod1;
    int prod2;

    //Loop infinito.
    while(true){
        //Adquire o lock do mutex.
        unique_lock<mutex> uniqueLock(*mtx);
        prod1 = 0;
        prod2 = 0;

        //Dorme por um tempo para simular a produção.
        sleep(rand() % 3 + 1);

        //O tabaqueiro não pode produzir ingredientes repetidos.
        while(prod1 == prod2){
            prod1 = rand() % 3;
            prod2 = rand() % 3;
        }

        //Alterna para true no vetor de produtos nos índices gerados.
        produto[prod1] = 1;
        produto[prod2] = 1;



        cout << endl << "Tabaqueiro produziu: ";
        if(prod1 == 0 || prod2 == 0){
            cout << "[Papel] ";
        }

        if(prod1 == 1 || prod2 == 1){
            cout << "[Tabaco] ";
        }

        if(prod1 == 2 || prod2 == 2){
            cout << "[Fosforo]";
        }

        cout << endl << endl << endl;
        //Dorme por um tempo.
        sleep(rand() % 3 + 1);
        //Dá a notificação para um dos fumantes voltar a verificar se pode fumar.
        podeFumar->notify_one();
        //Libera o lock e espera pelo sinal para poder voltar a produzir.
        podeFornecer.wait(uniqueLock);
    }
}

#endif
