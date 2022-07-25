#ifndef UNTITLED_LISTADOBLEAVANZADA_H
#define UNTITLED_LISTADOBLEAVANZADA_H
#include <vector>
#include <map>
#include <iostream>
typedef struct NodoAvanzado{
    NodoAvanzado* siguiente= nullptr;
    NodoAvanzado* anterior= nullptr;
    NodoAvanzado* apAnt= nullptr;
    NodoAvanzado* apSig= nullptr;
    int dato;
}NodoAvanzado;
class listaDobleAvanzada{
public:
    listaDobleAvanzada();
    ~listaDobleAvanzada();
    void insertAv(int);
    void removerNodoAv(NodoAvanzado*);
    void setAp();
    NodoAvanzado* getHeadAv();
    NodoAvanzado* getTailAv();
private:
    void setApAnt(std::pair<int,int>, NodoAvanzado*);
    void setApSig(std::pair<int,int>, NodoAvanzado*);
    void insertAv(NodoAvanzado*, int);
    void insertFirstAv(int);
    NodoAvanzado* headAv=NULL;
    NodoAvanzado* tailAv=NULL;
};
#endif //UNTITLED_LISTADOBLEAVANZADA_H
