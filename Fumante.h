//  A classe Fumante possui como atributo somente uma variável de condição que é compartilhada entre todos os fumantes.
//  Além disso, possui dois construtores, o método Enrolar e o método Fumar.

#ifndef FUMANTE_H_INCLUDED
#define FUMANTE_H_INCLUDED
#include <condition_variable>
#include <mutex>

using namespace std;

class Fumante{

private:
    condition_variable* podeFumar;

public:
    Fumante();
    Fumante(condition_variable* _podeFumar);
    void Enrolar(mutex* mtx, condition_variable* podeFornecer, int produto[3], int fumante);
    void Fumar(mutex* mtx, condition_variable* podeFornecer, int produto[3], int fumante);
};

//  Construtor padrão.
Fumante::Fumante(){

}

//  Construtor recebe como parâmetro a referência da variável de condição que controlará as threads dos fumantes.
Fumante::Fumante(condition_variable* _podeFumar){
    podeFumar = _podeFumar;
}

//O método Enrolar() recebe como parâmetro a referência do mutex que é compartilhado entre todas as threads, a referência da
//variável de condição que controla a thread do Tabaqueiro, o vetor de produtos e o índice do fumante. Sua função é de criar
//um loop para verificar se determinado fumante possui o ingrediente neessário para fumar.
void Fumante::Enrolar(mutex* mtx, condition_variable* podeFornecer, int produto[3], int fumante){
    //Loop infinito..
    while(true){
    //Switch alternará para a verificação correta do respectivo fumante. Caso o índice do fumante seja 0, isso é, possui papel, verifique se
    //o vetor de produtos indica que possui os outros dois ingredientes para enrolar o cigarro. Se for verdade, chame o método Fumar().
    //O mesmo vale para os outros fumantes.
        switch(fumante){

        case 0:
            if(produto[1] == 1 && produto[2] == 1){
                Fumar(mtx, podeFornecer, produto,0);
            }

            break;

        case 1:
            if(produto[0] == 1 && produto[2] == 1){
                Fumar(mtx, podeFornecer, produto,1);
            }

            break;

        case 2:
            if(produto[0] == 1 && produto[1] == 1){
                Fumar(mtx, podeFornecer, produto,2);
            }

            break;
        }
    }
}

//O método Fumar() recebe como parâmetros a referência do mutex que é compartilhado entre todas as threads, a referência da variável de condição que
//controla a thread do tabaqueiro, o vetor de produtos e o índice do fumante.
void Fumante::Fumar(mutex* mtx, condition_variable* podeFornecer, int produto[3], int fumante){
    //A função possui o lock do mutex.
    unique_lock<mutex> uniqueLock(*mtx);
    cout << endl << "Fumante "<< fumante <<" esta Fumando" << endl;
    //O vetor de produtos é resetado.
    for(int i = 0; i < 3; i++){
        produto[i] = 0;
    }
    //Dorme por um tempo para simular.
    sleep(rand() % 3 + 1);

    cout << endl << "Fumante " << fumante << " acabou de fumar." << endl;
    cout << endl << endl;
    //Da o sinal para o tabaqueiro voltar a produzir.
    podeFornecer->notify_one();
    //Libera o lock e espera pelo sinal para poder voltar a verificar se pode fumar.
    podeFumar->wait(uniqueLock);
}

#endif
