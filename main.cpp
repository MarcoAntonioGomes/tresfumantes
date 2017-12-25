//  Membros do grupo:
//      Harley Vitor Santana de Brito   RA: 0022919
//      Marco Antônio Gomes             RA: 0022915
//      Samuel Trindade Silva           RA: 0022133
//      Raianny Magalhães Silva         RA: 0022116
//      Maíla Gonçalves de Oliveira     RA: 0011849

//  Para a solução do problema de sincronismo dos três fumantes no paradigma orientado a objetos foram utilizadas três classes:
//      A classe Mesa;
//      A classe Tabaqueiro;
//      A casse Fumante;

#include <iostream>
#include <mutex>
#include <condition_variable>
#include <thread>
#include "Tabaqueiro.h"
#include "Fumante.h"
#include "Mesa.h"

using namespace std;

int main(){
    cout << endl << "Hello Tres Fumantes." << endl;
    cout << endl << "O fumante 0 possui papel." << endl;
    cout << "O fumante 1 possui tabaco." << endl;
    cout << "O fumante 2 possui fosforo."<< endl;
    cout << endl << endl << endl;
    sleep(5);
    Mesa mesa;
    mesa.Iniciar();

    return 0;
}
