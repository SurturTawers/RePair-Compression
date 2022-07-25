#ifndef UNTITLED_LISTADOBLE_H
#define UNTITLED_LISTADOBLE_H
#include <iostream>
typedef struct Nodo{
    Nodo* siguiente;
    int dato;
    Nodo* anterior;
}Nodo;
class listaDoble{
public:
    listaDoble();
    ~listaDoble();
    void insert(int);
    void removerNodo(Nodo*);
    Nodo* getHead();
    Nodo* getTail();
private:
    void insert(Nodo*,int);
    void insertFirst(int);
    Nodo* head=NULL;
    Nodo* tail=NULL;
};
#endif //UNTITLED_LISTADOBLE_H
