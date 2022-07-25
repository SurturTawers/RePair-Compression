#ifndef UNTITLED_REPAIRAVANZADO_H
#define UNTITLED_REPAIRAVANZADO_H
#include <vector>
#include <map>
#include "maxHeap.h"
#include "listaDobleAvanzada.h"
typedef struct{
    NodoAvanzado* primAp=nullptr;
    NodoAvanzado* ultAp=nullptr;
    nodoHeap* pos=nullptr;
    int f;
}Node;
class rePairAvanzado{
public:
    rePairAvanzado();
    ~rePairAvanzado();
    std::vector<int> control(std::vector<int>&);
private:
    int sigma=28;
    maxHeap* mH;
    std::vector<int> sec_rPA;
    listaDobleAvanzada* lisDobAv;
    std::map<std::pair<int,int>,Node> mapa;
    void mapear();
    void datos(std::vector<int>&);
    std::vector<int> comprimir();
    void setPos();
    void modVal(NodoAvanzado*);

};
#endif //UNTITLED_REPAIRAVANZADO_H